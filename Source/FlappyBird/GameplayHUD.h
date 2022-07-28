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
	//class UUserWidget* EndWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	//class UUserWidget* ScoreWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPregameWidget> PregameWidgetClass;
	//class UUserWidget* PregameWidget;
	//class UUserWidget* CurrentWidget;
	class UScoreWidget* ScoreWidget;
	class UDeathScreenWidget* EndWidget;
	class UPregameWidget* PregameWidget;

	virtual void BeginPlay()override;
public:
	UFUNCTION()
	void showEnd(AActor* DestroyedActor);

	UFUNCTION()
	void showScore();

	UFUNCTION()
	void PregameStart();

	void clear();
};
