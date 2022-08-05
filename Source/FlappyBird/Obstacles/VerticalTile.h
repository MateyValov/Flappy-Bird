// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeObstacle.h"
#include "VerticalTile.generated.h"

UCLASS()
class FLAPPYBIRD_API AVerticalTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVerticalTile();
	UFUNCTION()
		virtual void Init(float givenSpeed);

protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root = nullptr;
	UPROPERTY(EditAnywhere)
		class UChildActorComponent* Bottom = nullptr;
	UPROPERTY(EditAnywhere)
		class UChildActorComponent* Top = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* ScoreBox = nullptr;
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* movement = nullptr;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class APipeObstacle> Pipe;

	UFUNCTION()
		void Action(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
