// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleGenerator.h"
#include "Components/BoxComponent.h"
#include "GapObstacle.h"
#include "GameplayModeBase.h"
#include "FlappyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleGenerator::AObstacleGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(root);
}


void AObstacleGenerator::generate()
{
	
	float gapPosition = (FMath::RandRange(-100, 325));
	//float gapPosition = (FMath::RandRange(150, 150));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("spawn"));
	AGapObstacle* obst = nullptr;
	obst = (AGapObstacle*)GetWorld()->SpawnActor<AGapObstacle>(FVector(GetActorLocation().X, GetActorLocation().Y,gapPosition), Rotation, SpawnInfo);
	
	obst->Init(Speed);

	GetWorldTimerManager().SetTimer(spawnHandle, this, &AObstacleGenerator::generate, SpawnTime, false);
}

void AObstacleGenerator::Init(float GivenSpeed, float GivenSpawnTime)
{
	Speed = GivenSpeed;
	SpawnTime = GivenSpawnTime;
}
