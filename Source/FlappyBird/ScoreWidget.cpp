// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::NativeConstruct()
{
	
}

void UScoreWidget::SetScore(int Score)
{
	CurrentScore->SetText(FText::FromString(FString::FromInt(Score)));
}
