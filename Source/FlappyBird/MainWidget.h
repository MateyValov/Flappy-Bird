// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FButtonClicked);

UCLASS()
class FLAPPYBIRD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	private:

		bool bImpossibleUnlocked = false;

		UFUNCTION()
			void OnPlayClicked();
		UFUNCTION()
			void OnQuitClicked();
		UFUNCTION()
			void OnOptionsClicked();
		UFUNCTION()
			void OnTitleClicked();
	protected:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* ImpossibleDifficultyUnlock;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UTextBlock* NewDifficulty;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* Play;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* Quit;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* Options;
		

		virtual void NativeConstruct() override;
	public:
		FButtonClicked OptionsClicked;
		FButtonClicked TitleClicked;
};
