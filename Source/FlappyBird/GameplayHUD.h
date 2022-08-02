// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ScoreWidget.h"
#include "PregameWidget.h"
#include "DeathScreenWidget.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()
protected:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDeathScreenWidget> EndWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPregameWidget> PregameWidgetClass;

	//UPROPERTY()
	class UScoreWidget* ScoreWidget;
	//UPROPERTY()
	class UDeathScreenWidget* EndWidget;
	//UPROPERTY()
	class UPregameWidget* PregameWidget;

	virtual void BeginPlay()override;

	void Clear();

public:
	UFUNCTION()
	void ShowEnd();

	UFUNCTION()
	void ShowScore();

	UFUNCTION()
	void PregameStart();

	
};
