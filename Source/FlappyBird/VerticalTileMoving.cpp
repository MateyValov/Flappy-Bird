// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalTileMoving.h"
#include "Components/BoxComponent.h"

void AVerticalTileMoving::Init(float givenSpeed)
{
	int RandBool = (FMath::RandRange(0, 1));
	if (RandBool == 0) {
		MovesUp = false;
	}
	else {
		MovesUp = true;
	}

	Speed = givenSpeed;

	movement->Velocity = FVector(0, -Speed, 0);
	movement->InitialSpeed = Speed;
	movement->MaxSpeed = movement->InitialSpeed;

	SwitchDirection();
}

void AVerticalTileMoving::SwitchDirection()
{
	switch (MovesUp) {
	case true:
		movement->Velocity = FVector(0, -Speed, 50);
		MovesUp = false;
		break;

	case false:
		movement->Velocity = FVector(0, -Speed, -50);
		MovesUp = true;
		break;
	}

	GetWorldTimerManager().SetTimer(DirectionHandle, this, &AVerticalTileMoving::SwitchDirection, 2, false);
}
