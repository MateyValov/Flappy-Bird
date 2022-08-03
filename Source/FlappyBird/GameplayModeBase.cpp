// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUD.h"
#include "FlappyController.h"
#include "OptionsSave.h"


void AGameplayModeBase::BeginPlay()
{
	if (UGameplayStatics::DoesSaveGameExist("Options", 0)) {
		LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		
		Difficulty = LoadedGame->CurrentDifficulty;

		if (LoadedGame->DifficultyScores.Contains(Difficulty)) {
			HighScore = LoadedGame->DifficultyScores[Difficulty];
		}
		else {
			LoadedGame->DifficultyScores.Add(Difficulty, 0);
		}
	}
	else {
		Difficulty = "Easy";
		HighScore = 0;
	}

	CurrentSettings = *DifficultySettings.Find(Difficulty);
		 
	//UpdateHighScore(nullptr);
	ABird* bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	bird->Init(CurrentSettings.WorldGravity, CurrentSettings.BirdJumpForce);
	
	AObstacleGenerator* generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	if (Difficulty == "Extreme") {
		generator->Init(CurrentSettings.ObstacleSpeed, 400 / CurrentSettings.ObstacleSpeed, CurrentSettings.TileToSpawn, true);
	}
	else {
		generator->Init(CurrentSettings.ObstacleSpeed, 400 / CurrentSettings.ObstacleSpeed, CurrentSettings.TileToSpawn, false);
	}

	AFlappyController* PlayerController = Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->StartDelegate.AddDynamic(generator, &AObstacleGenerator::generate);
	PlayerController->StartDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::ShowScore);

	bird->OnGameEnd.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), & AGameplayHUD::ShowEnd);
	bird->OnGameEnd.AddDynamic(this, &AGameplayModeBase::OnGameEnd);
}

void AGameplayModeBase::SetScore(int Points)
{
	Score = Points;
	OnScoreUpdated.Broadcast(Score);
}

void AGameplayModeBase::UnlockDifficulty(FString DifficultyToUnlock)
{
	LoadedGame->UnlockDifficulty(DifficultyToUnlock);
	OnDifficultyUlocked.ExecuteIfBound(DifficultyToUnlock);
}

void AGameplayModeBase::OnGameEnd()
{

	if (HighScore < Score) {
		HighScore = Score;
		
		LoadedGame->DifficultyScores.Add(Difficulty, HighScore);
		
	}
	TArray<FString> AllDifficulties;
	DifficultySettings.GenerateKeyArray(AllDifficulties);

	if (CurrentSettings.ScoreToAdvance!= -1 && HighScore >= CurrentSettings.ScoreToAdvance) {

		int IndexToCheck = AllDifficulties.IndexOfByKey(Difficulty) + 1;
		if (AllDifficulties.IsValidIndex(IndexToCheck)) {
			UnlockDifficulty(AllDifficulties[IndexToCheck]);
		}
	}

	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);

	OnHighScoreUpdated.Broadcast(HighScore);

	OnDifficultyLoaded.ExecuteIfBound(Difficulty);
}





