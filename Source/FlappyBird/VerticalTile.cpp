// Fill out your copyright notice in the Description page of Project Settings.

#include "VerticalTile.h"
#include "Bird.h"
#include "ObstacleGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayModeBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AVerticalTile::AVerticalTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Bottom = CreateDefaultSubobject<UChildActorComponent>(TEXT("Bottom Pipe"));
	Bottom->SetChildActorClass(Pipe);
	Bottom->SetupAttachment(Root);

	Top = CreateDefaultSubobject<UChildActorComponent>(TEXT("Top Pipe"));
	Top->SetChildActorClass(Pipe);
	Top->SetupAttachment(Root);

	score = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	score->OnComponentBeginOverlap.AddDynamic(this, &AVerticalTile::Action);
	score->SetupAttachment(Root);

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	movement->ProjectileGravityScale = 0;
}

void AVerticalTile::Init(float givenSpeed)
{
	movement->Velocity = FVector(0, -givenSpeed, 0);
	movement->InitialSpeed = givenSpeed;
	movement->MaxSpeed = movement->InitialSpeed;
}

void AVerticalTile::Action(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		int points = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(points);
		return;
	}

	AObstacleGenerator* gen = Cast<AObstacleGenerator>(OtherActor);
	if (gen != nullptr) {
		Bottom->DestroyChildActor();
		Top->DestroyChildActor();
		Destroy();
	}
}

// Called every frame
void AVerticalTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

