// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAPPYBIRD_API SScoreWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SScoreWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameplayHUD>, OwningHUD)
	SLATE_END_ARGS()

	TWeakObjectPtr<class AGameplayHUD> OwningHUD;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
