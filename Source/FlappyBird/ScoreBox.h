// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBox.generated.h"

UCLASS()
class FLAPPYBIRD_API AScoreBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreBox();
	UFUNCTION()
		void Init(float givenSpeed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float speed;
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
