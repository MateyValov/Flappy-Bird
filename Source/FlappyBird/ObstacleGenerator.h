// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bird.h"
#include "VerticalTile.h"
#include "ObstacleGenerator.generated.h"

UENUM()
enum class EObstacleGap {
	Bottom, Mid, Top
};

UCLASS()
class FLAPPYBIRD_API AObstacleGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleGenerator();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(EditAnywhere)
		float DefaultSpeed = 200;
	UPROPERTY(EditAnywhere)
		float DefficultyAddition = 150;
	UPROPERTY(VisibleAnywhere)
		float Speed;
	UPROPERTY(VisibleAnywhere)
		float SpawnTime = 2;
	UPROPERTY(EditAnywhere)
		float TileSize = 80;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AVerticalTile> Spawnable;
	
	FTimerHandle spawnHandle;

	FRotator Rotation;
	FActorSpawnParameters SpawnInfo;
	
	//EObstacleGap direction = EDirectionType::Forward;

public:	
	void Init(float GivenSpeed, float GivenSpawnTime);

	UFUNCTION()
	void generate();
};
