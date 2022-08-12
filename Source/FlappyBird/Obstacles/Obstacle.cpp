// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"
#include "../Character/Bird.h"
#include "../GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APipeObstacle::APipeObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APipeObstacle::OnBeginOverlap);
	//MeshComponent->SetupAttachment(Root);
	SetRootComponent(MeshComponent);
}


void APipeObstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OverlapedCharacter = Cast<ACharacter>(OtherActor);
	if (OverlapedCharacter != nullptr) {
		OverlapedCharacter->TakeDamage(1, FDamageEvent::FDamageEvent(), OverlapedCharacter->Controller, this);
	}
}



