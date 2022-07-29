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
	/*UPROPERTY(EditAnywhere)
		float Defaultgravity = 1;
	
	UPROPERTY(EditAnywhere)
		float DefficultyAddition = 0.6;
	UPROPERTY(EditAnywhere)
		float DefaultjumpForce = 500;*/
	UPROPERTY(VisibleAnywhere)
		float Gravity;
	UPROPERTY(VisibleAnywhere)
		float JumpForce;

	bool bPressed = false;

protected:
	/*UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;*/
	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* MeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* Hitbox = nullptr; 
	/*UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArm = nullptr;*/
	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* Camera = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		class UAnimationAsset* AnimAsset = nullptr;

public:	

	void Jump();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void EndGame(AActor* DestroyedActor);

	UFUNCTION()
		void Init(float GivenGravity, float GivenJumpForce);

};
