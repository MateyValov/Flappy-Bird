// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"


void UOptionsWidget::OnExitClicked()
{
	ExitClicked.Broadcast();
	
}

void UOptionsWidget::OnSaveClicked()
{
	SaveClicked.Broadcast();

}


void UOptionsWidget::OnBindSelected(FInputChord SelectedKey)
{
	BindingChanged.ExecuteIfBound(FInputActionKeyMapping("Jump", SelectedKey.Key));
}


void UOptionsWidget::OnDifficultySelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	DifficultySelected.ExecuteIfBound(SelectedItem);
}


void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectDifficulty->OnSelectionChanged.AddDynamic(this, &UOptionsWidget::OnDifficultySelected);
	Exit->OnClicked.AddDynamic(this, &UOptionsWidget::OnExitClicked);
	JumpBindingSelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBindSelected);
	JumpBindingSelector->KeySelectionText = FText::FromString("Press any Button");
	Save->OnClicked.AddDynamic(this, &UOptionsWidget::OnSaveClicked);
	//SelectDifficulty->SetSelectedOption("Easy");
}


void UOptionsWidget::UpdateOptions(FString CurrentDifficulty, TSet<FString> Difficulties, FInputActionKeyMapping OldJumpBind)
{

	JumpBindingSelector->SetSelectedKey(OldJumpBind.Key);

	SelectDifficulty->ClearOptions();
	for (FString diff : Difficulties) {
		SelectDifficulty->AddOption(diff);
	}

	SelectDifficulty->SetSelectedOption(CurrentDifficulty);
}
