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
		dificulty = LoadedGame->Difficulty;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, dificulty);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, LoadedGame->JumpBind);
	}
	UpdateHighScore();
	ABird* bird = GetWorld()->SpawnActor<ABird>(PawnClass, BirdSpawnLocation, FRotator());
	bird->Init(DifficultySettings.Find(dificulty)->WorldGravity, DifficultySettings.Find(dificulty)->BirdJumpForce);
	
	AObstacleGenerator* generator = GetWorld()->SpawnActor<AObstacleGenerator>(GeneratorClass, GeneratorPosition, FRotator());
	generator->Init(DifficultySettings.Find(dificulty)->ObstacleSpeed, 400/ DifficultySettings.Find(dificulty)->ObstacleSpeed);

	Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.AddDynamic(generator, &AObstacleGenerator::generate);
}

void AGameplayModeBase::UpdateHighScore()
{
	if (UGameplayStatics::DoesSaveGameExist(dificulty, 0)) {
		UHighScore* LoadedGame = Cast<UHighScore>(UGameplayStatics::LoadGameFromSlot(dificulty, 0));
		HighScore = LoadedGame->HighScore;
	}
	
}


