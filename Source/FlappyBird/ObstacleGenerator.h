// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleGenerator.generated.h"

UCLASS()
class FLAPPYBIRD_API AObstacleGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(VisibleAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		float TileSize = 80;

	FTimerHandle spawnHandle;

	enum class EObstacleGap {
		Bottom, Mid ,Top 
	};
	//EObstacleGap direction = EDirectionType::Forward;

	UFUNCTION()
		void generate();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
