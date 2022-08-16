// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::OnPlayClicked()
{
	PlayClicked.Broadcast();
}

void UMainWidget::OnQuitClicked()
{
	QuitClicked.Broadcast();
}

void UMainWidget::OnOptionsClicked()
{
	OptionsClicked.Broadcast();
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Quit->OnClicked.AddDynamic(this, &UMainWidget::OnQuitClicked);
	Play->OnClicked.AddDynamic(this, &UMainWidget::OnPlayClicked);
	Options->OnClicked.AddDynamic(this, &UMainWidget::OnOptionsClicked);
	ImpossibleDifficultyUnlock->OnClicked.AddDynamic(this, &UMainWidget::OnTitleClicked);
}

void UMainWidget::OnTitleClicked()
{
	if (bImpossibleUnlocked) return;
	bImpossibleUnlocked = true;
	TitleClicked.Broadcast();
}