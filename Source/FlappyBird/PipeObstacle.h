// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PipeObstacle.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeObstacle();
	UFUNCTION()
	void Init(float givenSpeed);

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh = nullptr;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* movement = nullptr;

	UFUNCTION()
	void kill(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
