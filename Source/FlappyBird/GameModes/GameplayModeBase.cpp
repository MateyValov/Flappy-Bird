// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/GameplayHUD.h"
#include "../Controller/FlappyBirdController.h"
#include "Blueprint/UserWidget.h"


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

	CurrentSettings = LoadedGame->CurrentDifficultySettings;
		 
	//UpdateHighScore(nullptr);
	ABird* bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	bird->Init(CurrentSettings.WorldGravity, CurrentSettings.BirdJumpForce);
	
	AObstacleGenerator* generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	generator->Init(CurrentSettings.ObstacleSpeed, 400 / CurrentSettings.ObstacleSpeed, CurrentSettings.TileToSpawn);

	AFlappyBirdController* PlayerController = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->StartDelegate.AddDynamic(generator, &AObstacleGenerator::Generate);
	PlayerController->StartDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::ShowScore);
	PlayerController->PauseDelegate.BindDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::TogglePause);

	bird->OnGameEnd.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), & AGameplayHUD::ShowEnd);
	bird->OnGameEnd.AddDynamic(this, &AGameplayModeBase::OnGameEnd);
	bird->OnScoreUpdated.AddDynamic(this, &AGameplayModeBase::ScoreUp);
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

void AGameplayModeBase::PlayAgain()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void AGameplayModeBase::MainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AGameplayModeBase::Quit()
{
	if (APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		pc->ConsoleCommand("quit");
	}
}

void AGameplayModeBase::ScoreUp()
{
	SetScore(GetScore()+1);
}

void AGameplayModeBase::OnGameEnd()
{

	if (HighScore < Score) {
		HighScore = Score;
		
		LoadedGame->DifficultyScores.Add(Difficulty, HighScore);
		
	}
	TArray<FString> AllDifficulties;
	//DifficultySettings.GenerateKeyArray(AllDifficulties);

	if (CurrentSettings.ScoreToAdvance!= -1 && HighScore >= CurrentSettings.ScoreToAdvance) {

			UnlockDifficulty(LoadedGame->CurrentDifficultySettings.DifficultyToUnlock);	
	}

	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);

	OnHighScoreUpdated.Broadcast(HighScore);

	OnDifficultyLoaded.ExecuteIfBound(Difficulty);
}





