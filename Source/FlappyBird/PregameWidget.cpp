// Fill out your copyright notice in the Description page of Project Settings.


#include "PregameWidget.h"

void UPregameWidget::NativeConstruct()
{
	Super::NativeDestruct();
	jumptostart->SetText(FText::FromString("Press Jump to Start"));
}
