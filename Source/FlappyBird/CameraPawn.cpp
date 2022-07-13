// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "Components/BoxComponent.h"
#include "Flappy.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->SetupAttachment(root);
	
	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	floor->SetupAttachment(root);
	roof = CreateDefaultSubobject<UBoxComponent>(TEXT("Roof"));
	roof->SetupAttachment(floor);
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(floor);
	
	
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraPawn::jumpSignal()
{
	JumpDelegate.ExecuteIfBound();
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACameraPawn::jumpSignal);
}

