// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyBirdController.h"
#include "../Character/Bird.h"

void AFlappyBirdController::Jump()
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
	switch (bIsPaused) {
	case true:
		bIsPaused = false;
		break;
	case false:
		bIsPaused = true;
		break;
	}

	PauseDelegate.ExecuteIfBound(bIsPaused);
	SetPause(bIsPaused);
}


void AFlappyBirdController::SetControlledCharacter(ACharacter* InCharacter)
{
	ControlledCharacter = InCharacter;
}

void AFlappyBirdController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFlappyBirdController::Jump);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AFlappyBirdController::Pause).bExecuteWhenPaused = true;
}