// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostPickUp.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoostPickUp::ABoostPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABoostPickUp::OnOverlap);

	AmmoPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionBoxMesh"));
	AmmoPackMesh->SetupAttachment(CollisionBox);

}

// Called when the game starts or when spawned
void ABoostPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoostPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoostPickUp::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);
	if (PlayerPawn)
	{
		PlayerPawn->BoostAmount += 2;
		SetActorEnableCollision(false);
	}

}

