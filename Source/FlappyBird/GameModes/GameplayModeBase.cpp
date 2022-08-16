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
	ABird* Bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	Bird->Init(CurrentSettings.WorldGravity, CurrentSettings.BirdJumpForce);
	
	AObstacleGenerator* Generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	Generator->Init(CurrentSettings.ObstacleSpeed, 400 / CurrentSettings.ObstacleSpeed, CurrentSettings.TileToSpawn);

	AFlappyBirdController* PlayerController = Cast<AFlappyBirdController>(Bird->Controller);
	PlayerController->/*Get*/StartDelegate.AddDynamic(Generator, &AObstacleGenerator::Generate);
	PlayerController->/*Get*/StartDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::ShowScore);
	PlayerController->/*Get*/PauseDelegate.BindDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::TogglePause);
	PlayerController->/*Get*/EndDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::ShowEnd);

	PlayerController->SetControlledCharacter(Bird);


	Bird->OnGameEnd.AddDynamic(this, &AGameplayModeBase::GameOver);
	Bird->OnScoreUpdated.AddDynamic(this, &AGameplayModeBase::ScoreUp);

	//OnScoreUp.BindDynamic(Bird, &ABird::ScoreUp);
	OnGameOver.AddDynamic(PlayerController, &AFlappyBirdController::OnGameEnd);
}


void AGameplayModeBase::SetScore(int InScore)
{
	Score = InScore;
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
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		PC->ConsoleCommand("quit");
	}
}

void AGameplayModeBase::ScoreUp()
{
	SetScore(GetScore()+1);
}

void AGameplayModeBase::GameOver()
{

	if (HighScore < Score) {
		HighScore = Score;
		
		LoadedGame->DifficultyScores.Add(Difficulty, HighScore);
		
	}
	TArray<FString> AllDifficulties;
	//DifficultySettings.GenerateKeyArray(AllDifficulties);

	if (CurrentSettings.ScoreToAdvance!= -1 && HighScore >= CurrentSettings.ScoreToAdvance) {
		if ( !(LoadedGame->AvailableDifficulties.Contains(LoadedGame->CurrentDifficultySettings.DifficultyToUnlock)) ) {
			UnlockDifficulty(LoadedGame->CurrentDifficultySettings.DifficultyToUnlock);
		}
	}

	UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);

	OnHighScoreUpdated.Broadcast(HighScore);

	OnDifficultyLoaded.ExecuteIfBound(Difficulty);

	OnGameOver.Broadcast();
}





