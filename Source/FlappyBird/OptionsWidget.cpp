// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "MenuHUD.h"
#include "FlappyBirdGameModeBase.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "OptionsSave.h"


void UOptionsWidget::OnExitClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		Cast<AMenuHUD>(pc->GetHUD())->ShowMenu();
	}
}

void UOptionsWidget::OnSaveClicked()
{
	UOptionsSave* LoadedGame = nullptr;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
	}

	if (difficulty != "")LoadedGame->CurrentDifficulty = difficulty;

	if (!(jumpbind == Oldjumpbind)) {
		Settings->AddActionMapping(jumpbind);
		Settings->RemoveActionMapping(Oldjumpbind);
		Settings->SaveKeyMappings();

		Oldjumpbind = jumpbind;
	}
	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}


void UOptionsWidget::OnBindSelected(FInputChord SelectedKey)
{
	jumpbind = FInputActionKeyMapping("Jump", SelectedKey.Key);
}


void UOptionsWidget::OnDifficultySelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	difficulty = SelectedItem;
}


void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	TArray<FInputActionKeyMapping> JumpBindings;

	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		difficulty = LoadedGame->CurrentDifficulty;
	}

	SelectDifficulty->OnSelectionChanged.AddDynamic(this, &UOptionsWidget::OnDifficultySelected);
	SelectDifficulty->SetSelectedOption(difficulty);

	Exit->OnClicked.AddDynamic(this, &UOptionsWidget::OnExitClicked);

	jumpBinding->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBindSelected);
	jumpBinding->KeySelectionText = FText::FromString("Press any Button");
	Settings->GetActionMappingByName("Jump", JumpBindings);
	jumpBinding->SetSelectedKey(JumpBindings[0].Key);
	Oldjumpbind = JumpBindings[0];


	Save->OnClicked.AddDynamic(this, &UOptionsWidget::OnSaveClicked);
}


void UOptionsWidget::UpdateDifficulties(TSet<FString> Difficulties)
{
	SelectDifficulty->ClearOptions();

	for (FString diff : Difficulties) {
		SelectDifficulty->AddOption(diff);
	}
}
