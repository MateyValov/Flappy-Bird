// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleGenerator.h"
#include "Components/BoxComponent.h"
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


void AObstacleGenerator::Generate()
{
	if (Spawnable) {
		float gapPosition = (FMath::RandRange(-150, 150));
		AVerticalTile* VertTile = nullptr;
		VertTile = (AVerticalTile*)GetWorld()->SpawnActor<AVerticalTile>(Spawnable, FVector(GetActorLocation().X, GetActorLocation().Y, gapPosition), Rotation, SpawnInfo);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawned an obstacle"));
		
		VertTile->Init(Speed);

		GetWorldTimerManager().SetTimer(spawnHandle, this, &AObstacleGenerator::Generate, SpawnTime, false);
	}
}
void AObstacleGenerator::Init(float GivenSpeed, float GivenSpawnTime, TSubclassOf<class AVerticalTile> ObjectToSpawn)
{
	Speed = GivenSpeed;
	SpawnTime = GivenSpawnTime;
	Spawnable = ObjectToSpawn;
}
