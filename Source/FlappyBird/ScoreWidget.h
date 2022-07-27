// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentScore;

	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void SetScore(int32 Score);
};
