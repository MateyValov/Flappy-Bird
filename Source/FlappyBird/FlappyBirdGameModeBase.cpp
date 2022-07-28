// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/InputSettings.h"

#include "MenuHUD.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	//PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
	
}

void AFlappyBirdGameModeBase::BeginPlay()
{
	UOptionsSave* LoadedGame;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
	}
	else {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::CreateSaveGameObject(UOptionsSave::StaticClass()));
	}

	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}
