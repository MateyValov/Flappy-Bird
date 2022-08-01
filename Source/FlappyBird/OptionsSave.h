// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OptionsSave.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UOptionsSave : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	FString CurrentDifficulty = "Easy";

	UPROPERTY(EditDefaultsOnly)
	TSet<FString> AvailableDifficulties;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, int32> DifficultyScores;

	UFUNCTION()
	void UnlockDifficulty(FString DifficultyToUnlock);
};
