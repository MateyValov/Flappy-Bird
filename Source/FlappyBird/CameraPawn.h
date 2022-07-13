// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

DECLARE_DELEGATE(JumpSignature);

UCLASS()
class FLAPPYBIRD_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();
	JumpSignature JumpDelegate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* cam = nullptr;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* floor = nullptr;
	
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitbox = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* roof = nullptr;
	

	UFUNCTION()
		void jumpSignal();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
