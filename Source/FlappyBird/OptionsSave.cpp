// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsSave.h"

void UOptionsSave::UnlockDifficulty(FString DifficultyToUnlock)
{
	AvailableDifficulties.Add(DifficultyToUnlock);
}
