// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleGenerator.h"
#include "Components/BoxComponent.h"
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

// Called when the game starts or when spawned
void AObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();
	FString diff = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->dificulty;
	
	if (diff == "Easy") {
		speed = DefaultSpeed;
	}
	else if (diff == "Normal") {
		speed = DefaultSpeed + DefficultyAddition;
	}
	else if (diff == "Hard") {
		speed = DefaultSpeed + DefficultyAddition*2;
	}
	spawnTime = 4 / (speed / 100);
	
	Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.AddDynamic(this, &AObstacleGenerator::generate);
	
	
}

void AObstacleGenerator::generate()
{
	if (Spawnable) {
		float gapPosition = (FMath::RandRange(-150, 150));
		AVerticalTile* VertTile = nullptr;
		VertTile = (AVerticalTile*)GetWorld()->SpawnActor<AVerticalTile>(Spawnable, FVector(GetActorLocation().X, GetActorLocation().Y, gapPosition), Rotation, SpawnInfo);

		//((APipeObstacle*)VertTile->Bottom->GetChildActor())->Init(speed);
		//((APipeObstacle*)VertTile->Top->GetChildActor())->Init(speed);
		//VertTile->Init(speed);

		GetWorldTimerManager().SetTimer(spawnHandle, this, &AObstacleGenerator::generate, spawnTime, false);
	}
}
