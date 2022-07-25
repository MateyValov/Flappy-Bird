// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "FlappyController.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameplayModeBase.h"
#include "GameplayHUD.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movement->ProjectileGravityScale = 0;
	movement->Velocity = FVector(0, 0, 0);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/BirdMesh/BirdModel.BirdModel'"));
	mesh->SetSkeletalMesh(MeshObj.Object);
	mesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//mesh->SetGenerateOverlapEvents(true);
	//mesh->SetCollisionProfileName(FName("OverlapAll"));
	ConstructorHelpers::FObjectFinder<UAnimationAsset> anim(TEXT("AnimSequence'/Game/BirdMesh/BirdModel_Anim.BirdModel_Anim'"));
	AnimObj = anim.Object;
	
	
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(mesh);
	hitbox->SetRelativeScale3D(FVector(2.5, 2.5, 2.5));
	hitbox->SetRelativeLocation(FVector(0,-6,0));

	SetActorRotation(FRotator(0, 180, 0));
	//SetActorLocation(FVector(101.796166,738.922339,413.471660));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	camera->OrthoWidth = 1400;
	camera->SetWorldLocation(FVector(-520,810,325));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	
}



void ABird::Jump()
{
	if (!pressed) {
		FString diff = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->dificulty;

		if (diff == "Easy") {
			gravity = Defaultgravity;
		}
		else if (diff == "Normal") {
			gravity = Defaultgravity + DefficultyAddition;
		}
		else if (diff == "Hard") {
			gravity = Defaultgravity + DefficultyAddition * 2;
		}
		jumpForce = (DefaultjumpForce*2) - (DefaultjumpForce/ gravity);
		mesh->PlayAnimation(AnimObj,true);
		movement->InitialSpeed = jumpForce;
		movement->MaxSpeed = movement->InitialSpeed*2;
		movement->ProjectileGravityScale = gravity;
		Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.ExecuteIfBound();
		Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->BackgroundDelegate.ExecuteIfBound();
		pressed = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("castvame"));
		//Cast<AGameplayHUD>(UGameplayStatics::GetGameMode(GetWorld())->HUDClass)->showScore();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showScore();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("skachame"));
	movement->Velocity.Z = jumpForce;
	
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABird::Jump);
}


void ABird::die()
{
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
	Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
	//}
	//else if (scorePoint != nullptr) {
	//	int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
	//	Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(score);
	//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("tochka"));
	//}

}
