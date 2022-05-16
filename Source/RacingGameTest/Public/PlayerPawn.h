// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HoverComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class RACINGGAMETEST_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		UStaticMeshComponent* PlayerMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		USpringArmComponent* BackSpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		UCameraComponent* BackCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		float DriveSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UFloatingPawnMovement* PawnMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		int Ammo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		float BoostAmount = 5; // Fuel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		float MaxBoostAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		float BoostPower = 10000.f;



	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BulletSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStats")
		float AngularDamping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStats")
		float LinearDamping;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	bool bCanPlay = false;

private:
	void StartDriving();
	void StopDriving();

	void StartBreaking();
	void StopBreaking();

	void StartBoosting();
	void StopBoosting();

	bool bDriving = false;
	bool bBreaking = false;
	bool bBoosting = false;

	void MoveRight(float Value);
	float CurrentTurnSpeed;
	
	float RefillTimer;

	void Shooting();

	void SwitchCamera();
	bool bSwitchCamera = false;

	void SaveGame();
	void LoadGame();

};
