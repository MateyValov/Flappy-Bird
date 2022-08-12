// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGBlock.generated.h"

UCLASS()
class FLAPPYBIRD_API ABGBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGBlock();

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UDecalComponent* Decal = nullptr;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* MovementComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float Speed = 20;

	UPROPERTY(EditInstanceOnly)
	FVector SpawnLocation;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
