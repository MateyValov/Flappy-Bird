// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "MenuHUD.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::OnPlayClicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UMainWidget::OnQuitClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		pc->ConsoleCommand("quit");
	}

}

void UMainWidget::OnOptionsClicked()
{
	OptionsClicked.ExecuteIfBound();
	//UE_LOG(LogTemp, Warning, TEXT("Cukna Se Butona"));
	if (APlayerController* pc = GetOwningPlayer()) {
		Cast<AMenuHUD>(pc->GetHUD())->ShowOptions();
	}
	
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UMainWidget::OnPlayClicked);
	Quit->OnClicked.AddDynamic(this, &UMainWidget::OnQuitClicked);
	Options->OnClicked.AddDynamic(this, &UMainWidget::OnOptionsClicked);
	ImpossibleDifficultyUnlock->OnClicked.AddDynamic(this, &UMainWidget::OnTitleClicked);
	NewDifficulty->SetText(FText::FromString(""));
}

void UMainWidget::OnTitleClicked()
{
	if (bImpossibleUnlocked) return;
	bImpossibleUnlocked = true;
	TitleClicked.ExecuteIfBound();
	NewDifficulty->SetText(FText::FromString("New Difficulty Unlocked"));
}