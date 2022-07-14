// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flappy.h"
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
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(VisibleAnywhere)
		float speed = 2;
	UPROPERTY(EditAnywhere)
		float TileSize = 80;
	UPROPERTY(EditAnywhere)
		class AFlappy* flappy = nullptr;

	FTimerHandle spawnHandle;

	FVector bottom;
	FVector mid;
	FVector top;
	FRotator Rotation;
	FActorSpawnParameters SpawnInfo;
	
	//EObstacleGap direction = EDirectionType::Forward;
	UFUNCTION()
		void generate();
	UFUNCTION()
		void kill(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void registerObst(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
