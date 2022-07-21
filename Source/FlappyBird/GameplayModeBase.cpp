// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUD.h"
#include "OptionsSave.h"

AGameplayModeBase::AGameplayModeBase()
{
	HUDClass = AGameplayHUD::StaticClass();
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		dificulty = LoadedGame->Difficulty;
	}
	UpdateHighScore();
}
void AGameplayModeBase::UpdateHighScore()
{
	if (UGameplayStatics::DoesSaveGameExist(dificulty, 0)) {
		UHighScore* LoadedGame = Cast<UHighScore>(UGameplayStatics::LoadGameFromSlot(dificulty, 0));
		HighScore = LoadedGame->HighScore;
	}
	
}
