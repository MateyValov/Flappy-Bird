// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HighScore.h"
#include "GameplayModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameplayModeBase();

	UPROPERTY(BlueprintReadOnly)
		int score=0;
	UPROPERTY(BlueprintReadOnly)
		int HighScore = 0;;
	UFUNCTION()
		void SetScore(int points) { score = points; };
	UFUNCTION()
		int GetScore() { return score; };
	UFUNCTION()
		void UpdateHighScore();
};
