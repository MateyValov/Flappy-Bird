// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Obstacles/ObstacleGenerator.h"
#include "../Character/Bird.h"
#include "../SaveSystem/OptionsSave.h"
#include "GameplayModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreUpdatedSignature, int, Score);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDifficultyPassing, FString, Difficulty);
DECLARE_DYNAMIC_DELEGATE(FGetScoreSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverSignature);


UCLASS()
class FLAPPYBIRD_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetScore(int InScore) ;

	UFUNCTION()
	int GetScore() { return Score; };

	UFUNCTION()
	void UnlockDifficulty(FString DifficultyToUnlock);

	UFUNCTION()
	void PlayAgain();

	UFUNCTION()
	void MainMenu();

	UFUNCTION()
	void Quit();

	FScoreUpdatedSignature OnScoreUpdated;
	FScoreUpdatedSignature OnHighScoreUpdated;
	FDifficultyPassing OnDifficultyLoaded;
	FDifficultyPassing OnDifficultyUlocked;

	FGameOverSignature OnGameOver;

protected:

	UFUNCTION()
	void ScoreUp();

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	FVector BirdSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ABird> PawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AObstacleGenerator> GeneratorClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	FVector GeneratorPosition;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UOptionsSave* LoadedGame;

	UFUNCTION()
	void GameOver();

	int Score = 0;

	int32 HighScore = 0;

	FString Difficulty = "";

	FDifficultyProperties CurrentSettings;
};
