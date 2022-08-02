// Fill out your copyright notice in the Description page of Project Settings.


#include "PregameWidget.h"

void UPregameWidget::NativeConstruct()
{
	Super::NativeDestruct();
	JumpToStart->SetText(FText::FromString("Press Jump to Start"));
}
