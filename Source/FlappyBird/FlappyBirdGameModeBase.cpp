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
