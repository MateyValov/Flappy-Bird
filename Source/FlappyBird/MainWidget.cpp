// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::OnPlayClicked()
{
	FLatentActionInfo LatentInfo;
	//UGameplayStatics::LoadStreamLevel(this, "Game", true, true, LatentInfo);
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
	//OwningHUD->hideMenu();
	//return FReply::Handled();
}

void UMainWidget::OnQuitClicked()
{
	//if (OwningHUD.IsValid()) {
		if (APlayerController* pc = GetOwningPlayer()) {
			pc->ConsoleCommand("quit");
		}
	//}*/
	//return FReply::Handled();

}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UMainWidget::OnPlayClicked);
	Quit->OnClicked.AddDynamic(this, &UMainWidget::OnQuitClicked);
	UE_LOG(LogTemp, Warning, TEXT("I just started crashing"));
}