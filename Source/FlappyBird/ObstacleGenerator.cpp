// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleGenerator.h"
#include "Components/BoxComponent.h"
#include "Obstacle.h"
#include "ScoreBox.h"
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
	hitbox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleGenerator::registerObst);
	hitbox->OnComponentEndOverlap.AddDynamic(this, &AObstacleGenerator::kill);
}

// Called when the game starts or when spawned
void AObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();
	//speed = Cast<AGameplayGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->speed;
	bottom = GetActorLocation();
	mid = bottom;
	mid.Z += TileSize*3;
	top = mid;
	top.Z += TileSize*3;
	if (flappy != nullptr) {
		flappy->StartDelegate.BindUFunction(this, FName("generate"));
	}
	
}

void AObstacleGenerator::generate()
{
	

	EObstacleGap GapPosition = static_cast<EObstacleGap>(FMath::RandRange(0, 2));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("spawn"));
	AObstacle* obst1 = nullptr;
	AObstacle* obst2 = nullptr;
	AScoreBox* score = nullptr;
	if (GapPosition == EObstacleGap::Bottom) {
		score = (AScoreBox*)GetWorld()->SpawnActor<AScoreBox>(bottom, Rotation, SpawnInfo);
		obst1 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(mid, Rotation, SpawnInfo);
		obst2 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(top, Rotation, SpawnInfo);
	}
	else if (GapPosition == EObstacleGap::Mid) {
		obst1 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(bottom, Rotation, SpawnInfo);
		score = (AScoreBox*)GetWorld()->SpawnActor<AScoreBox>(mid, Rotation, SpawnInfo);
		obst2 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(top, Rotation, SpawnInfo);
	}
	else if (GapPosition == EObstacleGap::Top) {
		obst1 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(bottom, Rotation, SpawnInfo);
		obst2 = (AObstacle*)GetWorld()->SpawnActor<AObstacle>(mid, Rotation, SpawnInfo);
		score = (AScoreBox*)GetWorld()->SpawnActor<AScoreBox>(top, Rotation, SpawnInfo);
	}
	obst1->Init(speed);
	obst2->Init(speed);
	score->Init(speed);

	GetWorldTimerManager().SetTimer(spawnHandle, this, &AObstacleGenerator::generate, 4/speed, false);
}

void AObstacleGenerator::kill(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("izleze"));
	AObstacle* obst = Cast<AObstacle>(OtherActor);
	if (obst != nullptr) {
		obst->Destroy();
		
	}
}

void AObstacleGenerator::registerObst(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("vleze"));
}

// Called every frame
void AObstacleGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

