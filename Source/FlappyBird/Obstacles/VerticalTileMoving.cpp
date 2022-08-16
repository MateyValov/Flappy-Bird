// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalTileMoving.h"
#include "Components/BoxComponent.h"

void AVerticalTileMoving::Init(float InSpeed)
{

	Super::Init(InSpeed);
	int RandBool = (FMath::RandRange(0, 1));
	if (RandBool == 0) {
		bMovesUp = false;
	}
	else {
		bMovesUp = true;
	}

	SwitchDirection();
}

void AVerticalTileMoving::SwitchDirection()
{
	switch (bMovesUp) {
	case true:
		MovementComponent->Velocity.Z = VerticalSpeed;
		bMovesUp = false;
		break;

	case false:
		MovementComponent->Velocity.Z = -VerticalSpeed;
		bMovesUp = true;
		break;
	}

	GetWorldTimerManager().SetTimer(DirectionHandle, this, &AVerticalTileMoving::SwitchDirection, 2, false);
}
