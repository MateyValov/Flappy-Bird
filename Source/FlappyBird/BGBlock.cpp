// Fill out your copyright notice in the Description page of Project Settings.

#include "BGBlock.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "BackgroundSpawner.h"
#include "GameplayModeBase.h"
#include "FlappyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABGBlock::ABGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movement->ProjectileGravityScale = 0;
	movement->Velocity = FVector(0, -Speed, 0);
	movement->InitialSpeed = Speed;
	movement->MaxSpeed = movement->InitialSpeed;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABGBlock::teleport);

	decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	decal->SetupAttachment(mesh);
}

void ABGBlock::teleport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABackgroundSpawner* spawner = Cast<ABackgroundSpawner>(OtherActor);
	if (spawner != nullptr) {
		SetActorLocation(FVector(2600, 2466, 0));
	}
	return;
}


