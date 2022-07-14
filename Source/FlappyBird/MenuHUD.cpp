// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMenuCompoundWidget.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	showMenu();
}

void AMenuHUD::showMenu()
{
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMenuCompoundWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetConteiner, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	
	}

}

void AMenuHUD::hideMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetConteiner.ToSharedRef());
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}
