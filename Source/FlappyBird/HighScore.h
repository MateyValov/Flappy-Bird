// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScore.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UHighScore : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
		int HighScore = 0;
	//UHighScore();
};
