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
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> EndWidgetClass;
	//class UUserWidget* EndWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	//class UUserWidget* ScoreWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PregameWidgetClass;
	//class UUserWidget* PregameWidget;
	class UUserWidget* CurrentWidget;

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime) override;
public:
	void showEnd();
	void showScore();
	void PregameStart();

	void clear();
};
