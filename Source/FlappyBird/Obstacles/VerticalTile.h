// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.h"
#include "VerticalTile.generated.h"

UCLASS()
class FLAPPYBIRD_API AVerticalTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVerticalTile();
	UFUNCTION()
	virtual void Init(float InSpeed);

protected:

	UPROPERTY(EditAnywhere)
	class USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* BottomPipe = nullptr;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* TopPipe = nullptr;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* ScoreBox = nullptr;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class APipeObstacle> Pipe;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Despawn();
	
};
