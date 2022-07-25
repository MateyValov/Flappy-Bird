// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayModeBase.h"
#include "Engine.h"
#include "BackgroundSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayModeBase.h"
#include "FlappyController.h"
#include "Kismet/GameplayStatics.h"

#include "BackgroundBlock.h"

// Sets default values
ABackgroundBlock::ABackgroundBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movement->ProjectileGravityScale = 0;
	movement->Velocity = FVector(0, 0, 0);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	mesh->SetupAttachment(root);
	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionProfileName("OverlapAll");
	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABackgroundBlock::teleport);

	decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	decal->SetupAttachment(mesh);
	
}

// Called when the game starts or when spawned
void ABackgroundBlock::BeginPlay()
{
	Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.AddDynamic(this, &ABackgroundBlock::Init);
	movement->InitialSpeed = speed;
	movement->MaxSpeed = movement->InitialSpeed*2;
	//movement->Velocity = FVector(0, 0, 0);
}

void ABackgroundBlock::Init()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("DVIJA SE BE"));
	movement->Velocity.Y = -speed;
}

void ABackgroundBlock::teleport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABackgroundSpawner* spawner = Cast<ABackgroundSpawner>(OtherActor);
	if (spawner != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("umrq"));
		SetActorLocation(FVector(2572, 2708, -97));
	}
}


