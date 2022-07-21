// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"


UCLASS()
class FLAPPYBIRD_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	UPROPERTY(EditAnywhere)
		float gravity = 1;
	UPROPERTY(EditAnywhere)
		float jumpForce = 500;
	bool pressed = false;

protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* mesh = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* camera = nullptr;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* movement = nullptr;
	UPROPERTY(EditAnywhere)
		class UAnimationAsset* AnimObj = nullptr;

public:	

	void Jump();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void die();

};
