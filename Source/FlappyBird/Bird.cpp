// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "FlappyController.h"
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
	
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	OnDestroyed.AddDynamic(this, &ABird::EndGame);
}

void ABird::Init(float GivenGravity, float GivenJumpForce)
{
	Gravity = GivenGravity;
	JumpForce = GivenJumpForce;
}

void ABird::Jump()
{
	if (!bPressed) {
		FString diff = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->dificulty;

		/*if (diff == "Easy") {
			gravity = Defaultgravity;
		}
		else if (diff == "Normal") {
			gravity = Defaultgravity + DefficultyAddition;
		}
		else if (diff == "Hard") {
			gravity = Defaultgravity + DefficultyAddition * 2;
		}
		jumpForce = (DefaultjumpForce*2) - (DefaultjumpForce/ gravity);*/
		Camera->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		//Camera->SetWorldLocation(FVector(-90.552462,805.948150,397.890182));

		MeshComponent->PlayAnimation(AnimAsset,true);
		MovementComponent->InitialSpeed = JumpForce;
		MovementComponent->MaxSpeed = MovementComponent->InitialSpeed*2;
		MovementComponent->ProjectileGravityScale = Gravity;
		Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.Broadcast();
		//Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->BackgroundDelegate.ExecuteIfBound();
		bPressed = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("castvame"));
		//Cast<AGameplayHUD>(UGameplayStatics::GetGameMode(GetWorld())->HUDClass)->showScore();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showScore();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("skachame"));
	MovementComponent->Velocity.Z = JumpForce;
	
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABird::Jump);
}


void ABird::EndGame(AActor* DestoyedActor)
{	
	
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
	Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
	
}


