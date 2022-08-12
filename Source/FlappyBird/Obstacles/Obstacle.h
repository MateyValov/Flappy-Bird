// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Obstacle.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APipeObstacle();

protected:

	//UPROPERTY(EditAnywhere)
	//class USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
