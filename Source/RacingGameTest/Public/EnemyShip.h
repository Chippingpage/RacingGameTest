// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "HoverComponent.h"
#include "EnemyShip.generated.h"

UCLASS()
class RACINGGAMETEST_API AEnemyShip : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere)
		UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyVariables")
		UStaticMeshComponent* EnemyMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UFloatingPawnMovement* CharacterMovementComponent = nullptr;


	//A sphere that if the Player enters, triggers the NPC to follow Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		class USphereComponent* PlayerSensingSphere{ nullptr };

	//The Controller for the NCP - similar to the PlayerController
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		class AAIController* AIController{ nullptr };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


};
