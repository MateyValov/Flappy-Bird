// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "../GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//UE_LOG(LogTemp, Warning, TEXT("PUSNA SE GAMEPLAY HUDA"));

	PregameWidget = Cast<UPregameWidget>(CreateWidget<UUserWidget>(GetWorld(), PregameWidgetClass));
	EndWidget = Cast<UDeathScreenWidget>(CreateWidget<UUserWidget>(GetWorld(), EndWidgetClass));
	ScoreWidget = Cast<UScoreWidget>(CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass));
	PauseWidget = Cast<UPauseWidget>(CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

	PauseWidget->MenuClicked.AddDynamic(GameMode, &AGameplayModeBase::MainMenu);

	EndWidget->PlayClicked.AddDynamic(GameMode, &AGameplayModeBase::PlayAgain);
	EndWidget->MainClicked.AddDynamic(GameMode, &AGameplayModeBase::MainMenu);
	EndWidget->QuitClicked.AddDynamic(GameMode, &AGameplayModeBase::Quit);

	GameMode->OnScoreUpdated.AddDynamic(ScoreWidget, &UScoreWidget::SetScore);
	GameMode->OnScoreUpdated.AddDynamic(EndWidget, &UDeathScreenWidget::SetScore);
	GameMode->OnHighScoreUpdated.AddDynamic(EndWidget, &UDeathScreenWidget::SetHighScore);
	GameMode->OnDifficultyLoaded.BindDynamic(EndWidget, &UDeathScreenWidget::SetDifficulty);
	GameMode->OnDifficultyUlocked.BindDynamic(EndWidget, &UDeathScreenWidget::SetDifficultyUlocked);

	PregameStart();
}


void AGameplayHUD::ShowEnd()
{
	Clear();
	
	if (PlayerOwner && EndWidget) {
		EndWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}


void AGameplayHUD::ShowScore()
{
	Clear();
	
	if (PlayerOwner && ScoreWidget) {
		ScoreWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}

}

void AGameplayHUD::ShowPause()
{
	Clear();

	if (PlayerOwner && PauseWidget) {
		PauseWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}

void AGameplayHUD::TogglePause(bool IsPaused)
{
	if (IsPaused) {
		ShowPause();
	}
	else {
		ShowScore();
	}	
}

void AGameplayHUD::PregameStart()
{
	Clear();
	
	if (PlayerOwner && PregameWidget) {
		PregameWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}


void AGameplayHUD::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}


