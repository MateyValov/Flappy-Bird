// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonClicked.h"
#include "DeathScreenWidget.generated.h"

/**
 * 
 */

UCLASS()
class FLAPPYBIRD_API UDeathScreenWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Play;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Quit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Main;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Difficulty;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* NewDifficulty;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CurrentScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* HighScore;

	UFUNCTION()
		void OnPlayClicked();
	UFUNCTION()
		void OnQuitClicked();
	UFUNCTION()
		void OnMainClicked();

	virtual void NativeConstruct() override;

public:
	FButtonClicked PlayClicked;
	FButtonClicked QuitClicked;
	FButtonClicked MainClicked;

	UFUNCTION()
		void SetScore(int32 Score);

	UFUNCTION()
		void SetHighScore(int32 Score);

	UFUNCTION()
		void SetDifficulty(FString Diff);

	UFUNCTION()
		void SetDifficultyUlocked(FString Diff);

};
