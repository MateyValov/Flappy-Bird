// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PregameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UPregameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* jumptostart;

		virtual void NativeConstruct() override;
};
