// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::NativeConstruct()
{
	GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}
