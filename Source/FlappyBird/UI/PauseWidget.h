// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ButtonClicked.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* Menu;

	UFUNCTION()
		void OnMenuClicked();

	virtual void NativeConstruct() override;

public:
	FButtonClicked MenuClicked;
};
