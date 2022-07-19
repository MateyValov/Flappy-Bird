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
	//TSharedPtr<class SMenuCompoundWidget> MenuWidget;
	//TSharedPtr<class SWidget> MenuWidgetConteiner;

	//class MainWidget* MenuWidget;
	TSubclassOf<class UUserWidget> MenuMenuWidgetClass;
	class UUserWidget* MenuWidget;
	
	//TSharedPtr<class Widget> MenuWidgetConteiner;
	virtual void BeginPlay()override;
public:
	void showMenu();
	void hideMenu();
};
