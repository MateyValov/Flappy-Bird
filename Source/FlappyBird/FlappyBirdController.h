// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyBirdController.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSignature);

UCLASS()
class FLAPPYBIRD_API AFlappyBirdController : public APlayerController
{
    GENERATED_BODY()
public:
    FStartSignature StartDelegate;
};