// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "SScoreWidget.h"
#include "SDeathScreenWidget.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	//showMenu();
}

void AGameplayHUD::showEnd()
{
	if (GEngine && GEngine->GameViewport) {
		EndWidget = SNew(SDeathScreenWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(EndWidgetConteiner, SWeakWidget).PossiblyNullContent(EndWidget.ToSharedRef()));
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}

	}

}

void AGameplayHUD::hideEnd()
{
	if (GEngine && GEngine->GameViewport && EndWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(EndWidgetConteiner.ToSharedRef());
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AGameplayHUD::showScore()
{
	if (GEngine && GEngine->GameViewport) {
		ScoreWidget = SNew(SScoreWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(ScoreWidgetConteiner, SWeakWidget).PossiblyNullContent(ScoreWidget.ToSharedRef()));
	}

}

void AGameplayHUD::hideScore()
{
	if (GEngine && GEngine->GameViewport && ScoreWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(ScoreWidgetConteiner.ToSharedRef());
	}
}
