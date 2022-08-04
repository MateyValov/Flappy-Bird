// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreenWidget.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

void UDeathScreenWidget::OnPlayClicked()
{
	//FLatentActionInfo LatentInfo;
	//UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UDeathScreenWidget::OnQuitClicked()
{
	/*
	if (APlayerController* pc = GetOwningPlayer()) {
		pc->ConsoleCommand("quit");
	}
	*/
}

void UDeathScreenWidget::OnMainClicked()
{
	/*
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	*/
}

void UDeathScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &AGameplayModeBase::OnPlayClicked);
	Quit->OnClicked.AddDynamic(this, &AGameplayModeBase::OnQuitClicked);
	Main->OnClicked.AddDynamic(this, &AGameplayModeBase::OnMainClicked);
	
}

void UDeathScreenWidget::SetScore(int32 Score)
{
	CurrentScore->SetText(FText::FromString(FString::FromInt(Score)));
}

void UDeathScreenWidget::SetHighScore(int32 Score)
{
	HighScore->SetText(FText::FromString(FString::FromInt(Score)));
}

void UDeathScreenWidget::SetDifficulty(FString Diff)
{
	Difficulty->SetText(FText::FromString(Diff));
}

