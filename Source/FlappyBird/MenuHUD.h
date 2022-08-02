// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainWidget.h"
#include "OptionsWidget.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AMenuHUD : public AHUD
{
	GENERATED_BODY() 
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOptionsWidget> OptionsWidgetClass;

	class UMainWidget* MainMenuWidget;
	class UOptionsWidget* OptionsWidget;

	void Clear();

	virtual void BeginPlay()override;

public:
	void ShowMenu();
	void ShowOptions();
};
