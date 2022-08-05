// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsSave.h"

void UOptionsSave::UnlockDifficulty(FString DifficultyToUnlock)
{
	AvailableDifficulties.Add(DifficultyToUnlock);
}

void UOptionsSave::SortDifficulties()
{
	TArray<FString> AllDificulties;
	TSet<FString> SortedDifficulties;
	DifficultySettings.GenerateKeyArray(AllDificulties);

	for (FString Difficulty : AllDificulties) {
		if (AvailableDifficulties.Contains(Difficulty)) {
			SortedDifficulties.Add(Difficulty);
		}
	}

	AvailableDifficulties = SortedDifficulties;
}
