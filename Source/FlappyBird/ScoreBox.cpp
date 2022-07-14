// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBox.h"
#include "Components/BoxComponent.h"

// Sets default values
AScoreBox::AScoreBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(root);
	hitbox->SetRelativeScale3D(FVector(0.6, 0.6, 2.4));
}

// Called when the game starts or when spawned
void AScoreBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreBox::Init(float givenSpeed)
{
	speed = givenSpeed;
}

// Called every frame
void AScoreBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = GetActorLocation();
	newLocation.Y -= speed;
	SetActorLocation(newLocation);
}

