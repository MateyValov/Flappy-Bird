// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "BackgroundSpawner.h"

// Sets default values
ABackgroundSpawner::ABackgroundSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ABackgroundSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABackgroundSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

