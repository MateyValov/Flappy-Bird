// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "../GameModes/MainMenuModeBase.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PUSNA SE MENU HUDA"));
	AFlappyBirdGameModeBase* GameMode = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	MainMenuWidget = CreateWidget<UMainWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MainMenuWidgetClass);
	OptionsWidget = CreateWidget<UOptionsWidget>(UGameplayStatics::GetGameInstance(GetWorld()), OptionsWidgetClass);

	MainMenuWidget->OptionsClicked.AddDynamic(GameMode, &AFlappyBirdGameModeBase::UpdateOptionsSignal);
	MainMenuWidget->OptionsClicked.AddDynamic(this, &AMenuHUD::ShowOptions);
	MainMenuWidget->TitleClicked.AddDynamic(GameMode, &AFlappyBirdGameModeBase::UnlockImpossible);
	MainMenuWidget->PlayClicked.AddDynamic(GameMode, &AFlappyBirdGameModeBase::StartGame);
	MainMenuWidget->QuitClicked.AddDynamic(GameMode, &AFlappyBirdGameModeBase::QuitGame);

	GameMode->OnOptionsUpdateRequested.BindDynamic(OptionsWidget, &UOptionsWidget::UpdateOptions);

	OptionsWidget->ExitClicked.AddDynamic(this, &AMenuHUD::ShowMenu);
	OptionsWidget->SaveClicked.AddDynamic(GameMode, &AFlappyBirdGameModeBase::SaveOptions);
	OptionsWidget->BindingChanged.BindDynamic(GameMode, &AFlappyBirdGameModeBase::UpdateCurrentJumpBind);
	OptionsWidget->DifficultySelected.BindDynamic(GameMode, &AFlappyBirdGameModeBase::UpdateCurrentDifficulty);

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





