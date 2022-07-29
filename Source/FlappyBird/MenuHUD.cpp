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
	UE_LOG(LogTemp, Warning, TEXT("PUSNA SE MENU HUDA"));
	MainMenuWidget = CreateWidget<UMainWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MainMenuWidgetClass);
	OptionsWidget = CreateWidget<UOptionsWidget>(UGameplayStatics::GetGameInstance(GetWorld()), OptionsWidgetClass);
	OptionsWidget->UpdateDifficulties(Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetDifficulties());
	UE_LOG(LogTemp, Warning, TEXT("SUZDADOHA SE WIDGETITE"));
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	Clear();
	
	if (PlayerOwner && MainMenuWidget) {
		MainMenuWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
		UE_LOG(LogTemp, Warning, TEXT("MENUTO SE POKAZA"));
	}
	UE_LOG(LogTemp, Warning, TEXT("I TO USPESHNO"));
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





