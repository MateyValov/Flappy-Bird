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

// Called when the game starts or when spawned
void AObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();
	FString diff = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->dificulty;
	
	if (diff == "Easy") {
		speed = DefaultSpeed;
	}
	else if (diff == "Normal") {
		speed = DefaultSpeed + 150;
	}
	else if (diff == "Hard") {
		speed = DefaultSpeed + 300;
	}
	spawnTime = 4 / (speed / 100);
	//if (bird != nullptr) {
	Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.BindUFunction(this, FName("generate"));
	//}
	
}

void AObstacleGenerator::generate()
{
	
	float gapPosition = (FMath::RandRange(-150, 450));
	//float gapPosition = (FMath::RandRange(150, 150));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("spawn"));
	AGapObstacle* obst = nullptr;
	obst = (AGapObstacle*)GetWorld()->SpawnActor<AGapObstacle>(FVector(GetActorLocation().X, GetActorLocation().Y,gapPosition), Rotation, SpawnInfo);
	
	obst->Init(speed);

	GetWorldTimerManager().SetTimer(spawnHandle, this, &AObstacleGenerator::generate, spawnTime, false);
}
