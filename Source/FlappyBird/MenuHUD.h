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
	class UUserWidget* MenuWidget;

	
	virtual void BeginPlay()override;
public:

};
