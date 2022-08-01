// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndDelegate);

UCLASS()
class FLAPPYBIRD_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	UPROPERTY(VisibleAnywhere)
		float Gravity;
	UPROPERTY(VisibleAnywhere)
		float JumpForce;


	void Jump();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void EndGame();

	UFUNCTION()
		void Init(float GivenGravity, float GivenJumpForce);

	FGameEndDelegate OnGameEnd;

protected:
	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* MeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* Hitbox = nullptr; 
	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* Camera = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComponent = nullptr;
	/*UPROPERTY(EditDefaultsOnly)
		class UAnimationAsset* AnimAsset = nullptr;*/

private:

	bool bPressed = false;



};
