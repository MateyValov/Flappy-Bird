// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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
		class UTextBlock* difficulty;
	UFUNCTION()
		void OnPlayClicked();
	UFUNCTION()
		void OnQuitClicked();
	UFUNCTION()
		void OnMainClicked();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AGameplayModeBase* GameMode = nullptr;

	virtual void NativeConstruct() override;
};
