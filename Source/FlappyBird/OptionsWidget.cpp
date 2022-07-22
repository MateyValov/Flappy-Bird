// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "MenuHUD.h"
#include "FlappyBirdGameModeBase.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "OptionsSave.h"

void UOptionsWidget::OnEasyClicked()
{
	difficulty = "Easy";
	ResetDifficulty();
}

void UOptionsWidget::OnNormalClicked()
{
	difficulty = "Normal";	
	ResetDifficulty();

}

void UOptionsWidget::OnHardClicked()
{
	difficulty = "Hard";
	ResetDifficulty();
}



void UOptionsWidget::OnExitClicked()
{

	if (APlayerController* pc = GetOwningPlayer()) {
		Cast<AMenuHUD>(pc->GetHUD())->showMenu();
	}
}

void UOptionsWidget::OnSaveClicked()
{
	UOptionsSave* SaveGameInstance = Cast<UOptionsSave>(UGameplayStatics::CreateSaveGameObject(UOptionsSave::StaticClass()));

	
	if(difficulty != "")SaveGameInstance->Difficulty = difficulty;

	if (jumpbind != "" ) {
		UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
		Settings->AddActionMapping(FInputActionKeyMapping("Jump", FKey(FName(jumpbind))));
		//Settings->AddActionMapping(FInputActionKeyMapping("Jump","Space Bar"));
		Settings->RemoveActionMapping(FInputActionKeyMapping("Jump", FKey(FName(Oldjumpbind))));
		Settings->SaveKeyMappings();
		SaveGameInstance->JumpBind = jumpbind;
		Oldjumpbind = jumpbind;
		jumpbind = "";
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Options", 0);

	
}

void UOptionsWidget::OnBindSelected(FInputChord SelectedKey)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("selectna kluch"));
	jumpbind = SelectedKey.GetInputText().ToString();
}

void UOptionsWidget::ResetDifficulty()
{
	Easy->SetBackgroundColor(FLinearColor(1, 1, 1, 1));	
	Normal->SetBackgroundColor(FLinearColor(1, 1, 1, 1));
	Hard->SetBackgroundColor(FLinearColor(1, 1, 1, 1));

	//FString diff = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->difficulty;
	if (difficulty == "Easy") {
		Easy->SetBackgroundColor(FLinearColor( 0.130208,0.130208, 0.130208, 1));
	}
	else if (difficulty == "Normal") {
		Normal->SetBackgroundColor(FLinearColor(0.130208, 0.130208, 0.130208, 1));
	}
	else if (difficulty == "Hard") {
		Hard->SetBackgroundColor(FLinearColor(0.130208, 0.130208, 0.130208, 1));
	}
}

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//IsFocusable = false;
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		difficulty = LoadedGame->Difficulty;
		Oldjumpbind = LoadedGame->JumpBind;
	}
	Easy->OnClicked.AddDynamic(this, &UOptionsWidget::OnEasyClicked);
	Normal->OnClicked.AddDynamic(this, &UOptionsWidget::OnNormalClicked);
	Hard->OnClicked.AddDynamic(this, &UOptionsWidget::OnHardClicked);
	Exit->OnClicked.AddDynamic(this, &UOptionsWidget::OnExitClicked);
	jumpBinding->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBindSelected);
	jumpBinding->KeySelectionText = FText::FromString("Press any Button");
	jumpBinding->SetNoKeySpecifiedText(FText::FromString(Oldjumpbind));
	Save->OnClicked.AddDynamic(this, &UOptionsWidget::OnSaveClicked);
	ResetDifficulty();
}