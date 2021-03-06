// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackgroundSpawner.generated.h"

UCLASS()
class FLAPPYBIRD_API ABackgroundSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* hitbox = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
