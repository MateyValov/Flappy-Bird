// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::SetScore(int32 Score)
{
	CurrentScore->SetText(FText::FromString(FString::FromInt(Score)));
}
