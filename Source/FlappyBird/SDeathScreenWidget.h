// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FLAPPYBIRD_API SDeathScreenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDeathScreenWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameplayHUD>, OwningHUD)
	SLATE_END_ARGS()

	FReply OnPlayClicked() const;

	TWeakObjectPtr<class AGameplayHUD> OwningHUD;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
