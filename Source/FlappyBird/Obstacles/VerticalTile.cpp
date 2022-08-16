// Fill out your copyright notice in the Description page of Project Settings.

#include "VerticalTile.h"
#include "../Character/Bird.h"
#include "ObstacleGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "../GameModes/GameplayModeBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AVerticalTile::AVerticalTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BottomPipe = CreateDefaultSubobject<UChildActorComponent>(TEXT("Bottom Pipe"));
	BottomPipe->SetChildActorClass(Pipe);
	BottomPipe->SetupAttachment(Root);

	TopPipe = CreateDefaultSubobject<UChildActorComponent>(TEXT("Top Pipe"));
	TopPipe->SetChildActorClass(Pipe);
	TopPipe->SetupAttachment(Root);

	ScoreBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	ScoreBox->OnComponentBeginOverlap.AddDynamic(this, &AVerticalTile::OnBeginOverlap);
	ScoreBox->SetupAttachment(Root);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	MovementComponent->ProjectileGravityScale = 0;

}

void AVerticalTile::Init(float InSpeed)
{
	MovementComponent->Velocity = FVector(0, -InSpeed, 0);
	MovementComponent->InitialSpeed = InSpeed;
	MovementComponent->MaxSpeed = MovementComponent->InitialSpeed;

}

void AVerticalTile::Despawn()
{
	BottomPipe->DestroyChildActor();
	TopPipe->DestroyChildActor();
	Destroy();

}

void AVerticalTile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AObstacleGenerator* Generator = Cast<AObstacleGenerator>(OtherActor);
	if (IsValid(Generator)) {
		Despawn();
	}
}


