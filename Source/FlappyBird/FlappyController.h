// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyController.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(StartSignature);
DECLARE_DELEGATE(BackgroundSignature);

UCLASS()
class FLAPPYBIRD_API AFlappyController : public APlayerController
{
	GENERATED_BODY()
public:
		StartSignature StartDelegate;
		BackgroundSignature BackgroundDelegate;
};
