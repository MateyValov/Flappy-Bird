// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "FlappyBirdController.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameplayModeBase.h"
#include "GameplayHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->ProjectileGravityScale = 0;
	MovementComponent->Velocity = FVector(0, 0, 0);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Static Mesh"));
	
	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(MeshComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(MeshComponent);
	
}

void ABird::Init(float GivenGravity, float GivenJumpForce)
{
	Gravity = GivenGravity;
	JumpForce = GivenJumpForce;
}

void ABird::Jump()
{
	if (!bPressed) {
		Camera->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

		//MeshComponent->PlayAnimation(AnimAsset,true);
		MovementComponent->InitialSpeed = JumpForce;
		MovementComponent->MaxSpeed = MovementComponent->InitialSpeed*2;
		MovementComponent->ProjectileGravityScale = Gravity;
		Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.Broadcast();
		bPressed = true;
	}
	MovementComponent->Velocity.Z = JumpForce;
	
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABird::Jump);
}


void ABird::EndGame()
{	
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
	OnGameEnd.Broadcast();
	//Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
}


