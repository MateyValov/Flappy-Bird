// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "../Controller/FlappyBirdController.h"
#include "../Obstacles/VerticalTile.h"
#include "Components/CapsuleComponent.h"	
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABird::OnBeginOverlap);

	OnTakeAnyDamage.AddDynamic(this, &ABird::OnDamageTaken);
}

void ABird::Init(float InGravity, float InJumpForce)
{
	Gravity = InGravity;
	JumpForce = InJumpForce;
}

void ABird::ScoreUp()
{
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

void ABird::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVerticalTile* OverlapedTile = Cast<AVerticalTile>(OtherActor);
	if (OverlapedTile!=nullptr) {
		
		ScoreUp();
	}
}

void ABird::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	OnGameEnd.Broadcast();
}





