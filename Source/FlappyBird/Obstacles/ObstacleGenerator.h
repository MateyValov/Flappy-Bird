// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VerticalTile.h"
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
	//virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere)
	//class USceneComponent* root = nullptr;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Hitbox = nullptr;

	UPROPERTY(VisibleAnywhere)
	float ObstacleSpeed;

	UPROPERTY(VisibleAnywhere)
	float SpawnTime;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AVerticalTile> ObjectToSpawn;
	
	FTimerHandle SpawnHandle;

	FRotator Rotation;
	FActorSpawnParameters SpawnInfo;

public:	
	void Init(float InObstacleSpeed, float InSpawnTime, TSubclassOf<class AVerticalTile> InObjectToSpawn);

	UFUNCTION()
	void Generate();
};
