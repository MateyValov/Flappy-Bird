// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VerticalTile.h"
#include "VerticalTileMoving.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AVerticalTileMoving : public AVerticalTile
{
	GENERATED_BODY()

public:
	virtual void Init(float givenSpeed) override;

protected:
	UPROPERTY(VisibleAnywhere)
		float Speed;
	UPROPERTY(VisibleAnywhere)
		bool MovesUp;

	FTimerHandle DirectionHandle;

	UFUNCTION()
		void SwitchDirection();

};
