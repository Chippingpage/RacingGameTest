// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostPickUp.generated.h"

UCLASS()
class RACINGGAMETEST_API ABoostPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoostPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoostPickUp")
class UBoxComponent* CollisionBox{ nullptr };

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoostPickUp")
class UStaticMeshComponent* AmmoPackMesh{ nullptr };

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoostPickUp")
int BoostGiven;


UFUNCTION()
void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult);

};