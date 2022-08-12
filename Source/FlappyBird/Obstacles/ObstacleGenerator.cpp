// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleGenerator.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleGenerator::AObstacleGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(RootComponent);
	//SetRootComponent(Hitbox);
}


void AObstacleGenerator::Generate()
{
	if (IsValid(ObjectClassToSpawn)) {
		float gapPosition = (FMath::RandRange(-150, 150));
		AVerticalTile* VertTile = nullptr;
		VertTile = GetWorld()->SpawnActor<AVerticalTile>(ObjectClassToSpawn, FVector(GetActorLocation().X, GetActorLocation().Y, gapPosition), Rotation, SpawnInfo);
		
		VertTile->Init(ObstacleSpeed);

		GetWorldTimerManager().SetTimer(SpawnHandle, this, &AObstacleGenerator::Generate, SpawnTime, false);
	}
}
void AObstacleGenerator::Init(float InObstacleSpeed, float InSpawnTime, TSubclassOf<class AVerticalTile> InObjectClassToSpawn)
{
	ObstacleSpeed = InObstacleSpeed;
	SpawnTime = InSpawnTime;
	ObjectClassToSpawn = InObjectClassToSpawn;
}
