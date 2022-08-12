// Fill out your copyright notice in the Description page of Project Settings.

#include "BGBlock.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABGBlock::ABGBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComponent->ProjectileGravityScale = 0;
	MovementComponent->Velocity = FVector(0, -Speed, 0);
	MovementComponent->InitialSpeed = Speed;
	MovementComponent->MaxSpeed = MovementComponent->InitialSpeed;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABGBlock::OnBeginOverlap);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(MeshComponent);
}

void ABGBlock::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorLocation(SpawnLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("teleportna"));

}

