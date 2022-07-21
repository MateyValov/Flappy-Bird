// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "MenuHUD.h"
#include "FlappyBirdGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "OptionsSave.h"

void UOptionsWidget::OnEasyClicked()
{
	Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty = "Easy";
	ResetDifficulty();
}

void UOptionsWidget::OnNormalClicked()
{
	Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty = "Normal";	
	ResetDifficulty();

}

void UOptionsWidget::OnHardClicked()
{
	Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty = "Hard";
	ResetDifficulty();
}

void UOptionsWidget::OnExitClicked()
{
	FString diff = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty;
	UOptionsSave* SaveGameInstance = Cast<UOptionsSave>(UGameplayStatics::CreateSaveGameObject(UOptionsSave::StaticClass()));
	SaveGameInstance->Difficulty = diff;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Options", 0);

	if (APlayerController* pc = GetOwningPlayer()) {
		Cast<AMenuHUD>(pc->GetHUD())->showMenu();
	}
}

void UOptionsWidget::ResetDifficulty()
{
	Easy->SetBackgroundColor(FLinearColor(1, 1, 1, 1));	
	Normal->SetBackgroundColor(FLinearColor(1, 1, 1, 1));
	Hard->SetBackgroundColor(FLinearColor(1, 1, 1, 1));

	FString diff = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty;
	if (diff == "Easy") {
		Easy->SetBackgroundColor(FLinearColor( 0.130208,0.130208, 0.130208, 1));
	}
	else if (diff == "Normal") {
		Normal->SetBackgroundColor(FLinearColor(0.130208, 0.130208, 0.130208, 1));
	}
	else if (diff == "Hard") {
		Hard->SetBackgroundColor(FLinearColor(0.130208, 0.130208, 0.130208, 1));
	}
}

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Easy->OnClicked.AddDynamic(this, &UOptionsWidget::OnEasyClicked);
	Normal->OnClicked.AddDynamic(this, &UOptionsWidget::OnNormalClicked);
	Hard->OnClicked.AddDynamic(this, &UOptionsWidget::OnHardClicked);
	Exit->OnClicked.AddDynamic(this, &UOptionsWidget::OnExitClicked);
	ResetDifficulty();
}