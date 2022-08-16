// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyBirdController.h"
#include "../Character/Bird.h"

void AFlappyBirdController::Action()
{
	if (!bIsStarted) {
		StartDelegate.Broadcast();

		bIsStarted = true;
	}
	ControlledCharacter->Jump();
}

void AFlappyBirdController::OnGameEnd()
{
	SetPause(true);
	EndDelegate.Broadcast();
}

void AFlappyBirdController::Pause()
{
	PauseDelegate.Broadcast(this);
}


void AFlappyBirdController::SetControlledCharacter(ACharacter* InCharacter)
{
	ControlledCharacter = InCharacter;
}

void AFlappyBirdController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFlappyBirdController::Action);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AFlappyBirdController::Pause).bExecuteWhenPaused = true;
}