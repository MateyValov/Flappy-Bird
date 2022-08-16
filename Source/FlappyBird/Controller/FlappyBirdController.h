// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyBirdController.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseSignature, APlayerController*, Controller);


UCLASS()
class FLAPPYBIRD_API AFlappyBirdController : public APlayerController
{
    GENERATED_BODY()

private:

    virtual void SetupInputComponent() override;

    bool bIsStarted = false;

    class ACharacter* ControlledCharacter;


    UFUNCTION()
    void Action();

    //UFUNCTION()

public:
    FGameStateSignature StartDelegate;
    FGameStateSignature EndDelegate;
    FPauseSignature PauseDelegate;

    UFUNCTION()
    void OnGameEnd();

    virtual void Pause() override;

    void SetControlledCharacter(ACharacter* InCharacter);

};