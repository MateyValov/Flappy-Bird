// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Engine/Engine.h"

void AMenuHUD::showMenu()
{
	clear();
	CurrentWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MenuMenuWidgetClass);
	if (PlayerOwner && CurrentWidget) {
		CurrentWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}

void AMenuHUD::showOptions()
{
	clear();
	CurrentWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), OptionsWidgetClass);
	if (PlayerOwner && CurrentWidget) {
		CurrentWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}

void AMenuHUD::clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	showMenu();
}



