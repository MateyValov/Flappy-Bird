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
		UOptionsSave* LoadedGame = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot("Options", 0));
		Difficulty = LoadedGame->Difficulty;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, dificulty);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, LoadedGame->JumpBind);
	}
	//UpdateHighScore(nullptr);
	ABird* bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	bird->Init(DifficultySettings.Find(Difficulty)->WorldGravity, DifficultySettings.Find(Difficulty)->BirdJumpForce);
	
	AObstacleGenerator* generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	generator->Init(DifficultySettings.Find(Difficulty)->ObstacleSpeed, 400 / DifficultySettings.Find(Difficulty)->ObstacleSpeed);

	AFlappyController* PlayerController = Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->StartDelegate.AddDynamic(generator, &AObstacleGenerator::generate);
	PlayerController->StartDelegate.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), &AGameplayHUD::showScore);

	bird->OnDestroyed.AddDynamic(Cast<AGameplayHUD>(PlayerController->GetHUD()), & AGameplayHUD::showEnd);
	bird->OnDestroyed.AddDynamic(this, &AGameplayModeBase::UpdateHighScore);

}

void AGameplayModeBase::SetScore(int Points)
{
	Score = Points;
	OnScoreUpdated.Broadcast(Score);
}

void AGameplayModeBase::UpdateHighScore(AActor* DestroyedActor)
{
	if (UGameplayStatics::DoesSaveGameExist(Difficulty, 0)) {
		UHighScore* LoadedGame = Cast<UHighScore>(UGameplayStatics::LoadGameFromSlot(Difficulty, 0));
		HighScore = LoadedGame->HighScore;
	}

	if (HighScore < Score) {
		HighScore = Score;
		UHighScore* SaveGameInstance = Cast<UHighScore>(UGameplayStatics::CreateSaveGameObject(UHighScore::StaticClass()));
		SaveGameInstance->HighScore = HighScore;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, Difficulty, 0);
	
	}
	OnHighScoreUpdated.Broadcast(HighScore);
	
}


