// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Obstacles/VerticalTile.h"
#include "OptionsSave.generated.h"

/**
 * 
 */

USTRUCT()
struct FDifficultyProperties
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly)
		float WorldGravity;

	UPROPERTY(EditDefaultsOnly)
		float ObstacleSpeed;

	UPROPERTY(EditDefaultsOnly)
		float BirdJumpForce;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AVerticalTile> TileToSpawn;

	UPROPERTY(EditDefaultsOnly)
		int ScoreToAdvance;

	UPROPERTY(EditDefaultsOnly)
		FString DifficultyToUnlock;
};

UCLASS()
class FLAPPYBIRD_API UOptionsSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, FDifficultyProperties> DifficultySettings;

	UPROPERTY(EditDefaultsOnly)
	FDifficultyProperties CurrentDifficultySettings;

	UPROPERTY(EditDefaultsOnly)
	FString CurrentDifficulty = "Easy";

	UPROPERTY(EditDefaultsOnly)
	TSet<FString> AvailableDifficulties;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, int32> DifficultyScores;

	UFUNCTION()
	void UnlockDifficulty(FString DifficultyToUnlock);

	UFUNCTION()
		void SortDifficulties();
};
