// Fill out your copyright notice in the Description page of Project Settings.

#include "Bird.h"
#include "PipeObstacle.h"

// Sets default values
APipeObstacle::APipeObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &APipeObstacle::kill);

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movement->ProjectileGravityScale = 0;

}

void APipeObstacle::Init(float givenSpeed)
{
	movement->Velocity = FVector(0, -givenSpeed, 0);
	movement->InitialSpeed = givenSpeed;
	movement->MaxSpeed = movement->InitialSpeed;
}

void APipeObstacle::kill(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("umrq"));
		bird->Destroy(true);
	}
}



