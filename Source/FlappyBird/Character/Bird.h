// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Bird.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreUpdateDelegate);

UCLASS()
class FLAPPYBIRD_API ABird : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

	//UFUNCTION()
	//void SettupMovementComponent();

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void Init(float InGravity, float InJumpForce);

	UFUNCTION()
	void ScoreUp();

	FGameEndDelegate OnGameEnd;
	FScoreUpdateDelegate OnScoreUpdated;

protected:

	UPROPERTY(VisibleAnywhere)
	float Gravity;

	UPROPERTY(VisibleAnywhere)
	float JumpForce;

	//UPROPERTY(VisibleAnywhere)
	//int Score;

	//UPROPERTY(EditDefaultsOnly)
	//class USkeletalMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* Hitbox = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera = nullptr;

	//UPROPERTY(EditDefaultsOnly)
	//class UProjectileMovementComponent* MovementComponent = nullptr;
	
	virtual void Jump() override;

private:

	bool bStarted = false;


};
