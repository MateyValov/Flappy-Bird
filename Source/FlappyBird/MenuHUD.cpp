// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "FlappyBirdGameModeBase.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PUSNA SE MENU HUDA"));
	AFlappyBirdGameModeBase* GameMode = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MainMenuWidget = CreateWidget<UMainWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MainMenuWidgetClass);
	OptionsWidget = CreateWidget<UOptionsWidget>(UGameplayStatics::GetGameInstance(GetWorld()), OptionsWidgetClass);
	MainMenuWidget->OptionsClicked.BindDynamic(GameMode, &AFlappyBirdGameModeBase::UpdateDifficultiesSignal);
	GameMode->OnDifficultyUpdateRequested.BindDynamic(OptionsWidget, &UOptionsWidget::UpdateDifficulties);
	MainMenuWidget->TitleClicked.BindDynamic(GameMode, &AFlappyBirdGameModeBase::UnlockImpossible);
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	Clear();
	
	if (PlayerOwner && MainMenuWidget) {
		MainMenuWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}

void AMenuHUD::ShowOptions()
{
	Clear();
	
	if (PlayerOwner && OptionsWidget) {
		OptionsWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}

void AMenuHUD::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}





