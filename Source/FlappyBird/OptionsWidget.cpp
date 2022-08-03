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

	if (Difficulty != "") {
		LoadedGame->CurrentDifficulty = Difficulty;
		LoadedGame->CurrentDifficultySettings = *LoadedGame->DifficultySettings.Find(Difficulty);
	}
	if (!(JumpBind == OldJumpBind)) {
		InputSettings->AddActionMapping(JumpBind);
		InputSettings->RemoveActionMapping(OldJumpBind);
		InputSettings->SaveKeyMappings();

		OldJumpBind = JumpBind;
	}
	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
}


void UOptionsWidget::OnBindSelected(FInputChord SelectedKey)
{
	JumpBind = FInputActionKeyMapping("Jump", SelectedKey.Key);
}


void UOptionsWidget::OnDifficultySelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Difficulty = SelectedItem;
}


void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	TArray<FInputActionKeyMapping> JumpBindings;

	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		Difficulty = LoadedGame->CurrentDifficulty;
	}

	SelectDifficulty->OnSelectionChanged.AddDynamic(this, &UOptionsWidget::OnDifficultySelected);
	SelectDifficulty->SetSelectedOption(Difficulty);

	Exit->OnClicked.AddDynamic(this, &UOptionsWidget::OnExitClicked);

	JumpBindingSelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBindSelected);
	JumpBindingSelector->KeySelectionText = FText::FromString("Press any Button");
	InputSettings->GetActionMappingByName("Jump", JumpBindings);
	JumpBindingSelector->SetSelectedKey(JumpBindings[0].Key);
	OldJumpBind = JumpBindings[0];


	Save->OnClicked.AddDynamic(this, &UOptionsWidget::OnSaveClicked);
}


void UOptionsWidget::UpdateDifficulties(TSet<FString> Difficulties)
{
	SelectDifficulty->ClearOptions();

	for (FString diff : Difficulties) {
		SelectDifficulty->AddOption(diff);
	}
}
