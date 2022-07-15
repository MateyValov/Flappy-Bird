// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.h"
#include "Flappy.generated.h"

DECLARE_DELEGATE(StartSignature);

UCLASS()
class FLAPPYBIRD_API AFlappy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlappy();
	float verticalVelocity;
	UPROPERTY(VisibleAnywhere)
		float currGravity = 0;
	UPROPERTY(EditAnywhere)
		float gravity = 0;
	UPROPERTY(EditAnywhere)
		float jumpForce = 0;
	bool pressed = false;

	StartSignature StartDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(EditAnywhere)
		class ACameraPawn* cameraController = nullptr;
	UFUNCTION()
		void jump();

	UFUNCTION()
		void die(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

};
