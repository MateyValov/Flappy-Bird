// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "../Controller/FlappyBirdController.h"
#include "Components/SphereComponent.h"	
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(RootComponent);
	//MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);

	
	
	/*
MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Static Mesh"));*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	
}

void ABird::Init(float InGravity, float InJumpForce)
{
	Gravity = InGravity;
	JumpForce = InJumpForce;
}

void ABird::ScoreUp()
{
	//Score += 1;
	//Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(Score);
	OnScoreUpdated.Broadcast();
}

void ABird::Jump()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(bPressedJump));
	if (!bStarted) {
		Camera->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		bStarted = true;
		GetCharacterMovement()->GravityScale = Gravity;
		
	}
	GetCharacterMovement()->Velocity.Z = JumpForce;
	
}


void ABird::EndGame()
{	
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
	OnGameEnd.Broadcast();
	//Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
}


