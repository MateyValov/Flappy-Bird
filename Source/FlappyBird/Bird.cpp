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
	/*root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);*/

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->ProjectileGravityScale = 0;
	MovementComponent->Velocity = FVector(0, 0, 0);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Static Mesh"));
	//mesh->SetupAttachment(RootComponent);
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/BirdMesh/BirdModel.BirdModel'"));
	//mesh->SetSkeletalMesh(MeshObj.Object);
	//mesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	//mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	////mesh->SetGenerateOverlapEvents(true);
	////mesh->SetCollisionProfileName(FName("OverlapAll"));
	//ConstructorHelpers::FObjectFinder<UAnimationAsset> anim(TEXT("AnimSequence'/Game/BirdMesh/BirdModel_Anim.BirdModel_Anim'"));
	//AnimObj = anim.Object;
	
	
	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(MeshComponent);
	/*hitbox->SetRelativeScale3D(FVector(2.5, 2.5, 2.5));
	hitbox->SetRelativeLocation(FVector(0,-6,0));*/

	SetActorRotation(FRotator(0, 180, 0));
	//SetActorLocation(FVector(101.796166,738.922339,413.471660));
	/*SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(MeshComponent);*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(MeshComponent);
	/*camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	camera->OrthoWidth = 1400;*/
	//Camera->SetRelativeLocation(FVector(-520,810,325));
	
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	OnDestroyed.AddDynamic(this, &ABird::EndGame);
}



void ABird::Jump()
{
	if (!pressed) {
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

		MeshComponent->PlayAnimation(AnimAsset,true);
		MovementComponent->InitialSpeed = 0;//jumpForce;
		MovementComponent->MaxSpeed = MovementComponent->InitialSpeed*2;
		MovementComponent->ProjectileGravityScale = 1;// gravity;
		Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->StartDelegate.Broadcast();
		//Cast<AFlappyController>(UGameplayStatics::GetPlayerController(this, 0))->BackgroundDelegate.ExecuteIfBound();
		pressed = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("castvame"));
		//Cast<AGameplayHUD>(UGameplayStatics::GetGameMode(GetWorld())->HUDClass)->showScore();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showScore();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("skachame"));
	MovementComponent->Velocity.Z = 500;// jumpForce;
	
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
	//}
	//else if (scorePoint != nullptr) {
	//	int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
	//	Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(score);
	//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("tochka"));
	//}
}
