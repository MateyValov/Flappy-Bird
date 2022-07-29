// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUD.h"
#include "FlappyController.h"
#include "OptionsSave.h"

AGameplayModeBase::AGameplayModeBase()
{
	HUDClass = AGameplayHUD::StaticClass();
	//DefaultPawnClass = ABird::StaticClass();
}

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
	//UpdateHighScore(nullptr);
	ABird* bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	bird->Init(DifficultySettings.Find(Difficulty)->WorldGravity, DifficultySettings.Find(Difficulty)->BirdJumpForce);
	
	AObstacleGenerator* generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	generator->Init(DifficultySettings.Find(Difficulty)->ObstacleSpeed, 400 / DifficultySettings.Find(Difficulty)->ObstacleSpeed);

	AFlappyController* PlayerController = Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->StartDelegate.AddDynamic(generator, &AObstacleGenerator::generate);
	PlayerController->StartDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::ShowScore);

	bird->OnDestroyed.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), & AGameplayHUD::ShowEnd);
	bird->OnDestroyed.AddDynamic(this, &AGameplayModeBase::UpdateHighScore);
	bird->OnDestroyed.AddDynamic(this, &AGameplayModeBase::UpdateDifficulty);
}

void AGameplayModeBase::SetScore(int Points)
{
	Score = Points;
	OnScoreUpdated.Broadcast(Score);
}

void AGameplayModeBase::UpdateHighScore(AActor* DestroyedActor)
{

	if (HighScore < Score) {
		HighScore = Score;
		
		LoadedGame->DifficultyScores.Add(Difficulty, HighScore);
		
		UGameplayStatics::SaveGameToSlot(LoadedGame, "Options", 0);
	
	}
	OnHighScoreUpdated.Broadcast(HighScore);
	
}

void AGameplayModeBase::UpdateDifficulty(AActor* DestroyedActor)
{

	OnDifficultyLoaded.ExecuteIfBound(Difficulty);

}


