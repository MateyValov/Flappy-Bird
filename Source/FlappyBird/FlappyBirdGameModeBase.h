// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OptionsSave.h"
#include "FlappyBirdGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FDifficultyUpdateRequest, TSet<FString>, Difficulties);

UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
		AFlappyBirdGameModeBase();

		UFUNCTION()
		void UpdateDifficultiesSignal();
		UFUNCTION()
			void UnlockImpossible();
		FDifficultyUpdateRequest OnDifficultyUpdateRequested;

protected:
	//UOptionsSave* LoadedGame;
	virtual void BeginPlay() override;

	TSet<FString> AvailableDifficulties;


	UPROPERTY(EditDefaultsOnly, Category = "Starting Difficulties")
	TSet<FString> StartingDifficulties;
};
