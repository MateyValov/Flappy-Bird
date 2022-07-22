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
	UPROPERTY()
		FString Difficulty = "Easy";
	UPROPERTY()
		FString JumpBind = "Space Bar";
};
