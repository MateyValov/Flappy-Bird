// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackgroundBlock.generated.h"

UCLASS()
class FLAPPYBIRD_API ABackgroundBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundBlock();
	UFUNCTION()
	void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh = nullptr;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decal = nullptr;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* movement = nullptr;
	UPROPERTY(VisibleAnywhere)
	float speed = 400;

	
	UFUNCTION()
	void teleport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame

};
