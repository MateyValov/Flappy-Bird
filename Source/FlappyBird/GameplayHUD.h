// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()
protected:
	TSharedPtr<class SDeathScreenWidget> EndWidget;
	TSharedPtr<class SWidget> EndWidgetConteiner;

	TSharedPtr<class SScoreWidget> ScoreWidget;
	TSharedPtr<class SWidget> ScoreWidgetConteiner;

	TSharedPtr<class SPregameWidget> PregameWidget;
	TSharedPtr<class SWidget> PregameWidgetConteiner;
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime) override;
public:
	void showEnd();
	void showScore();
	void hideEnd();
	void hideScore();

	void PregameStart();
	void PregameStop();
};
