// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere)
			float speed = 100;
};
