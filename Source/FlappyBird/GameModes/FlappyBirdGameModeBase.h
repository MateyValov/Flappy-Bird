// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../SaveSystem/OptionsSave.h"
#include "GameFramework/InputSettings.h"
#include "FlappyBirdGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOptionsUpdateRequest, FString, CurrentDifficulty, TSet<FString>, Difficulties, FInputActionKeyMapping, OldJumpBind);



UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//AFlappyBirdGameModeBase();

	UFUNCTION()
	void UpdateOptionsSignal();

	UFUNCTION()
	void UpdateCurrentDifficulty(FString Selection);

	UFUNCTION()
	void UpdateCurrentJumpBind(FInputActionKeyMapping Selection);

	UFUNCTION()
	void UnlockImpossible();

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void SaveOptions();

	FOptionsUpdateRequest OnOptionsUpdateRequested;

protected:
	//UOptionsSave* LoadedGame;
	virtual void BeginPlay() override;

	TSet<FString> AvailableDifficulties;

	UInputSettings* InputSettings = nullptr;

	FString CurrentDifficulty;

	FInputActionKeyMapping CurrentJumpBind;

	FInputActionKeyMapping OldJumpBind;

	UPROPERTY(EditDefaultsOnly, Category = "Difficulty Settings")
	TMap<FString, FDifficultyProperties> DifficultySettings;

	UPROPERTY(EditDefaultsOnly, Category = "Difficulty Settings")
	TSet<FString> StartingDifficulties;
};
