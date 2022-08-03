// Fill out your copyright notice in the Description page of Project Settings.

#include "BGBlock.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "BackgroundSpawner.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABGBlock::ABGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComponent->ProjectileGravityScale = 0;
	MovementComponent->Velocity = FVector(0, -Speed, 0);
	MovementComponent->InitialSpeed = Speed;
	MovementComponent->MaxSpeed = MovementComponent->InitialSpeed;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABGBlock::Teleport);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(MeshComponent);
}

void ABGBlock::Teleport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABackgroundSpawner* spawner = Cast<ABackgroundSpawner>(OtherActor);
	if (spawner != nullptr) {

		SetActorLocation(SpawnLocation);
	}
	return;
}


