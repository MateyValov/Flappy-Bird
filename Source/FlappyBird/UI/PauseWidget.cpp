// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

void UPauseWidget::OnMenuClicked()
{
	MenuClicked.Broadcast();
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Menu->OnClicked.AddDynamic(this, &UPauseWidget::OnMenuClicked);
}
