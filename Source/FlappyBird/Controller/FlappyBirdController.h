// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyBirdController.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSignature);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPauseSignature, bool, IsPaused);

UCLASS()
class FLAPPYBIRD_API AFlappyBirdController : public APlayerController
{
    GENERATED_BODY()

private:

    bool bIsStarted = false;
    bool bIsPaused = false;

    class ACharacter* ControlledCharacter;


    UFUNCTION()
    void Jump();

    //UFUNCTION()
    virtual void Pause() override;

public:
    FStartSignature StartDelegate;
    FPauseSignature PauseDelegate;

    void SetControlledCharacter(ACharacter* InCharacter);

    virtual void SetupInputComponent() override;

};