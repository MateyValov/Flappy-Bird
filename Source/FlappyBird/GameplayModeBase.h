// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HighScore.h"
#include "ObstacleGenerator.h"
#include "Bird.h"
#include "GameplayModeBase.generated.h"

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
};

UCLASS()
class FLAPPYBIRD_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameplayModeBase();

	UPROPERTY(BlueprintReadOnly)
		int score=0;
	UPROPERTY(BlueprintReadOnly)
		int HighScore = 0;
	/*UPROPERTY(BlueprintReadOnly)
		float Speed = 0;*/
	UPROPERTY(BlueprintReadOnly)
		FString dificulty = "";
	UFUNCTION()
		void SetScore(int points) { score = points; };
	UFUNCTION()
		int GetScore() { return score; };
	UFUNCTION()
		void UpdateHighScore();
protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	FVector BirdSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ABird> PawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
		TSubclassOf<AObstacleGenerator> GeneratorClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
		FVector GeneratorPosition;

	UPROPERTY(EditDefaultsOnly, Category = "Difficulty Settings")
	TMap<FString, FDifficultyProperties> DifficultySettings;

	//UPROPERTY(EditDefaultsOnly, Category = "GameStart")

	virtual void BeginPlay() override;
};
