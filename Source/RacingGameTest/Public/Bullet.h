// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class RACINGGAMETEST_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletMesh")
		UStaticMeshComponent* BulletMesh = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "BulletThings")
		float BulletSpeed = 6000.f;

	UPROPERTY(EditAnywhere, Category = "Bulletthings")
		float TimeBeforeDestroy = 5.f;

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		float TimedLived = 0.f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
