// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/InputKeySelector.h"
#include "OptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Dificulty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Exit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Save;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UComboBoxString* SelectDifficulty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UInputKeySelector* jumpBinding;

	UFUNCTION()
		void OnExitClicked();
	UFUNCTION()
		void OnSaveClicked();
	UFUNCTION()
		void OnBindSelected(FInputChord SelectedKey);

	UFUNCTION()
		void OnDifficultySelected(FString SelectedItem, ESelectInfo::Type SelectionType);

	class UInputSettings* Settings = nullptr;
	

	FString difficulty = "";
	FInputActionKeyMapping jumpbind;
	FInputActionKeyMapping Oldjumpbind;

	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
		void UpdateDifficulties(TSet<FString> Difficulties);
};
