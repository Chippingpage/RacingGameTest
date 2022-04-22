// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"



// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(PlayerMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetupAttachment(PlayerMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	SpringArm->bUsePawnControlRotation = false;

	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;

	PlayerMesh->SetSimulatePhysics(true);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));


	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VehicleMeshComponent(TEXT("StaticMesh'/Game/Models/Player/Ship1.Ship1'"));
	if (VehicleMeshComponent.Succeeded())
	{
		PlayerMesh->SetStaticMesh(VehicleMeshComponent.Object);
	}
	PawnMovementComponent->MaxSpeed = 5000.f;

	AngularDamping = 5.0f;
	LinearDamping = 3.0f;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Forward = GetActorForwardVector();
	Forward.Z = 0;


	if (bDriving) 
	{
		AddMovementInput(FVector(Forward), DriveSpeed);
		PlayerMesh->SetAngularDamping(AngularDamping);
		PlayerMesh->SetLinearDamping(LinearDamping);
	}

	if (bBreaking) 
	{
		AddMovementInput(FVector(Forward), (-DriveSpeed/2));
	}

	if (bBoosting)
	{
		BoostAmount -= 0.05f;
		PlayerMesh->AddForce(Forward * BoostPower * PlayerMesh->GetMass());
		if (BoostAmount < 0.f)
		{
			bBoosting = false;
		}
	}

	if (!bBoosting)
	{
		RefillTimer += 0.01f;
		if (RefillTimer >= 1.f)
		{
			if (BoostAmount < 5.f)
			{
				BoostAmount += 0.01f;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Current BoostFuel: %f"), BoostAmount);

	float MaxDistance = 100.f;
	FVector EndLocation = GetActorLocation() + (GetActorUpVector() * -MaxDistance);
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), EndLocation, CollisionObjectQueryParams))
	{
		PlayerMesh->AddForce(GetActorUpVector() * 800.f * PlayerMesh->GetMass());
		//UE_LOG(LogTemp, Warning, TEXT("Tracer works"));
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Driving", IE_Pressed, this, &APlayerPawn::StartDriving);
	InputComponent->BindAction("Driving", IE_Released, this, &APlayerPawn::StopDriving);

	InputComponent->BindAction("Breaking", IE_Pressed, this, &APlayerPawn::StartBreaking);
	InputComponent->BindAction("Breaking", IE_Released, this, &APlayerPawn::StopBreaking);

	InputComponent->BindAction("Shooting", IE_Pressed, this, &APlayerPawn::Shooting);

	InputComponent->BindAction("Boost", IE_Pressed, this, &APlayerPawn::StartBoosting);
	InputComponent->BindAction("Boost", IE_Released, this, &APlayerPawn::StopBoosting);

	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);

}





void APlayerPawn::StartDriving()
{
	if (bCanPlay)
	{
		bDriving = true;
	}
}

void APlayerPawn::StopDriving()
{
	bDriving = false;
}

void APlayerPawn::StartBreaking()
{
	if (bCanPlay)
	{
		bBreaking = true;
	}
}

void APlayerPawn::StopBreaking()
{
	bBreaking = false;
}

void APlayerPawn::StartBoosting()
{
	if (bCanPlay) {
		if (BoostAmount > 0)
		{
			bBoosting = true;
		}
	}
}

void APlayerPawn::StopBoosting()
{
	RefillTimer = 0.f;
	bBoosting = false;
}

void APlayerPawn::MoveRight(float Value)
{
	if (bCanPlay)
	{
		FVector Forward = GetActorForwardVector();
		FVector Right = GetActorRightVector();

		// Gir smooth
		CurrentTurnSpeed = FMath::FInterpTo(CurrentTurnSpeed, Value, GetWorld()->GetDeltaSeconds(), 1.f);

		PlayerMesh->AddRelativeRotation(FRotator(0.f, 3.f, 0.f) * CurrentTurnSpeed);
	}
}

void APlayerPawn::Shooting()
{
	if (bCanPlay)
	{
		if (Ammo > 0) {
			Ammo--;

			UWorld* World = GetWorld();
			if (World)
			{

				FVector Location = GetActorLocation();
				FVector FwdVector = GetActorForwardVector();
				FwdVector *= 400;
				Location += FwdVector;
				World->SpawnActor<AActor>(BulletSpawn, Location, GetActorRotation());

			}
			UE_LOG(LogTemp, Warning, TEXT("Shooting"));
		}
	}

}





