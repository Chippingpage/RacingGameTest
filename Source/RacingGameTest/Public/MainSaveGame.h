// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */


UCLASS()
class RACINGGAMETEST_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMainSaveGame();
	UPROPERTY(EditAnywhere, Category = "SavingData")
		FString PlayerName;
	UPROPERTY(EditAnywhere, Category = "SavingData")
		int32 PlayerIndex;
	UPROPERTY(EditAnywhere, Category = Basic)
		FVector PlayerPosition {0.f, 0.f, 0.f};
	UPROPERTY(EditAnywhere, Category = Basic)
		FRotator PlayerRotation {0.f, 0.f, 0.f};
	UPROPERTY(VisibleAnywhere, Category = "SavingData")
		float BoostAmountSave;
	

};
