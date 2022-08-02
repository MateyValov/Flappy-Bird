// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFramework/InputSettings.h"


void AFlappyBirdGameModeBase::BeginPlay()
{
	UOptionsSave* LoadedGame;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
	}
	else {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::CreateSaveGameObject(UOptionsSave::StaticClass()));
	}

	for (FString diff : StartingDifficulties) {
		LoadedGame->AvailableDifficulties.Add(diff);
	}

	AvailableDifficulties = LoadedGame->AvailableDifficulties;


	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}

void AFlappyBirdGameModeBase::UpdateDifficultiesSignal() {

	OnDifficultyUpdateRequested.ExecuteIfBound(AvailableDifficulties);
}

void AFlappyBirdGameModeBase::UnlockImpossible()
{
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		LoadedGame->UnlockDifficulty("Impossible");
		AvailableDifficulties = LoadedGame->AvailableDifficulties;
		UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
	}
}
