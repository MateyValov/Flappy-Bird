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
	if (APlayerController* pc = GetOwningPlayer()) {
		Cast<AMenuHUD>(pc->GetHUD())->showOptions();
	}
	
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UMainWidget::OnPlayClicked);
	Quit->OnClicked.AddDynamic(this, &UMainWidget::OnQuitClicked);
	Options->OnClicked.AddDynamic(this, &UMainWidget::OnOptionsClicked);
}