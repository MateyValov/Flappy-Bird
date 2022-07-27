// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "HighScore.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	
	PregameWidget = Cast<UPregameWidget>(CreateWidget<UUserWidget>(GetWorld(), PregameWidgetClass));
	EndWidget = Cast<UDeathScreenWidget>(CreateWidget<UUserWidget>(GetWorld(), EndWidgetClass));
	ScoreWidget = Cast<UScoreWidget>(CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass));

	Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->OnScoreUpdated.AddDynamic(ScoreWidget, &UScoreWidget::SetScore);
	//Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->OnScoreUpdated.AddDynamic(this, &AGameplayHUD::showScore);
	PregameStart();
}


void AGameplayHUD::showEnd()
{
	clear();

	//----------ZA MESTENE V GAMEPLAYMODE----
	AGameplayModeBase* gamemode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	int HighScore = gamemode->HighScore;
	int score = gamemode->GetScore();

	if (HighScore < score) {
		
		UHighScore* SaveGameInstance = Cast<UHighScore>(UGameplayStatics::CreateSaveGameObject(UHighScore::StaticClass()));
		SaveGameInstance->HighScore = score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, gamemode->dificulty, 0);
		gamemode->UpdateHighScore();
	}
	//---------------------------------------
	
	if (PlayerOwner && EndWidget) {
		EndWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}


void AGameplayHUD::showScore()
{
	clear();
	
	if (PlayerOwner && ScoreWidget) {
		ScoreWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}

}


void AGameplayHUD::PregameStart()
{
	clear();
	
	if (PlayerOwner && PregameWidget) {
		PregameWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}


void AGameplayHUD::clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}


