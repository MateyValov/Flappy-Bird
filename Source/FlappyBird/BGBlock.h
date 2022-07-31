// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGBlock.generated.h"

UCLASS()
class FLAPPYBIRD_API ABGBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGBlock();

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh = nullptr;
	UPROPERTY(EditAnywhere)
		class UDecalComponent* decal = nullptr;
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* movement = nullptr;

	UPROPERTY(VisibleAnywhere)
		float Speed = 20;

	UFUNCTION()
		void teleport(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
