// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUD.h"

AGameplayModeBase::AGameplayModeBase()
{
	HUDClass = AGameplayHUD::StaticClass();
	UpdateHighScore();
	
}
void AGameplayModeBase::UpdateHighScore()
{
	if (UGameplayStatics::DoesSaveGameExist("HighScore", 0)) {
		UHighScore* LoadedGame = Cast<UHighScore>(UGameplayStatics::LoadGameFromSlot("HighScore", 0));
		HighScore = LoadedGame->HighScore;
	}
}
