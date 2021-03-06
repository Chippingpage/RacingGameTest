// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"
#include "AIController.h"
#include "PlayerPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"


// Sets default values
AEnemyShip::AEnemyShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(GetRootComponent());

	PlayerSensingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSensingSphere"));
	PlayerSensingSphere->SetupAttachment(GetRootComponent());
	PlayerSensingSphere->InitSphereRadius(650.f);



	GetCharacterMovement()->MaxAcceleration = 2000.f;
	GetCharacterMovement()->MaxWalkSpeed = 5000.f;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AIController)
	{
		AIController = Cast<AAIController>(GetController());
	}

	PlayerSensingSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyShip::OnOverlap);
}

// Called every frame
void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);
	if (PlayerPawn)
	{
		AIController->MoveToActor(PlayerPawn, 100);
		UE_LOG(LogTemp, Warning, TEXT("Moving"));
	}
}

