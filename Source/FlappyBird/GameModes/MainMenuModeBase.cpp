// Copyright Epic Games, Inc. All Rights Reserved.


#include "MainMenuModeBase.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFramework/InputSettings.h"


void AFlappyBirdGameModeBase::BeginPlay()
{
	InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	TArray<FInputActionKeyMapping> JumpBindings;
	InputSettings->GetActionMappingByName("Jump", JumpBindings);
	OldJumpBind = JumpBindings[0];
	CurrentJumpBind = OldJumpBind;

	UOptionsSave* LoadedGame;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
	}
	else {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::CreateSaveGameObject(UOptionsSave::StaticClass()));
		LoadedGame->CurrentDifficultySettings = *DifficultySettings.Find("Easy");

		for (FString diff : StartingDifficulties) {
			LoadedGame->AvailableDifficulties.Add(diff);
		}
	}

	LoadedGame->DifficultySettings = DifficultySettings;
	CurrentDifficulty = LoadedGame->CurrentDifficulty;
	LoadedGame->SortDifficulties();
	AvailableDifficulties = LoadedGame->AvailableDifficulties;

	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}


void AFlappyBirdGameModeBase::UpdateOptionsSignal() {
	OnOptionsUpdateRequested.ExecuteIfBound(CurrentDifficulty, AvailableDifficulties, OldJumpBind);
}


void AFlappyBirdGameModeBase::UpdateCurrentDifficulty(FString Selection)
{
	CurrentDifficulty = Selection;
}


void AFlappyBirdGameModeBase::UpdateCurrentJumpBind(FInputActionKeyMapping Selection)
{
	CurrentJumpBind = Selection;
}


void AFlappyBirdGameModeBase::UnlockImpossible()
{
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		if (LoadedGame->AvailableDifficulties.Contains("Impossible")) {
			return;
		}
		LoadedGame->UnlockDifficulty("Impossible");
		AvailableDifficulties = LoadedGame->AvailableDifficulties;
		UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
	}
}


void AFlappyBirdGameModeBase::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}


void AFlappyBirdGameModeBase::QuitGame()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		PC->ConsoleCommand("quit");
	}
}


void AFlappyBirdGameModeBase::SaveOptions()
{
	UOptionsSave* LoadedGame = nullptr;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
	}

	LoadedGame->CurrentDifficulty = CurrentDifficulty;
	LoadedGame->CurrentDifficultySettings = *LoadedGame->DifficultySettings.Find(CurrentDifficulty);
	
	if (!(CurrentJumpBind == OldJumpBind)) {
		InputSettings->AddActionMapping(CurrentJumpBind);
		InputSettings->RemoveActionMapping(OldJumpBind);
		InputSettings->SaveKeyMappings();

		OldJumpBind = CurrentJumpBind;
	}
	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}
