// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreenWidget.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

void UDeathScreenWidget::OnPlayClicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UDeathScreenWidget::OnQuitClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		pc->ConsoleCommand("quit");
	}

}

void UDeathScreenWidget::OnMainClicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void UDeathScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UDeathScreenWidget::OnPlayClicked);
	Quit->OnClicked.AddDynamic(this, &UDeathScreenWidget::OnQuitClicked);
	Main->OnClicked.AddDynamic(this, &UDeathScreenWidget::OnMainClicked);
	GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}