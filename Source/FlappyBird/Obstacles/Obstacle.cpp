// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"
#include "../Character/Bird.h"
#include "../GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APipeObstacle::APipeObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &APipeObstacle::kill);
}

void APipeObstacle::kill(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		//DON'T TOUCH THE GENGINE
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("umrq"));
		//bird->EndGame();
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver.ExecuteIfBound();
	}
}



