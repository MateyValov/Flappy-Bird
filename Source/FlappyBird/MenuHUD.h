// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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
	TSubclassOf<UUserWidget> MenuMenuWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OptionsWidgetClass;
	class UUserWidget* CurrentWidget;

	void clear();

	virtual void BeginPlay()override;

public:
	void showMenu();
	void showOptions();
};
