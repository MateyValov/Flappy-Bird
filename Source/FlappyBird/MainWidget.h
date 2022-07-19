// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	private:
	protected:
		//UPROPERTY(EditAnywhere)
		//	class AObstacle* perry;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* Play;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
			class UButton* Quit;
	public:
};
