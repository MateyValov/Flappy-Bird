// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameplayModeBase.h"
#include "GameplayHUD.h"
#include "ScoreBox.h"
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
	movement->Velocity.X = 0;
	movement->InitialSpeed = jumpForce;
	movement->MaxSpeed = movement->InitialSpeed;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	mesh->SetStaticMesh(MeshObj.Object);
	mesh->SetRelativeScale3D(FVector(0.8, 0.8, 0.8));

	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(mesh);
	hitbox->SetRelativeScale3D(FVector(1.42, 1.42, 1.58));

	SetActorRotation(FRotator(0, 0, 90));
	//SetActorLocation(FVector(101.796166,738.922339,413.471660));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
}



void ABird::Jump()
{
	if (!pressed) {
		movement->ProjectileGravityScale = gravity;
		StartDelegate.ExecuteIfBound();
		pressed = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("castvame"));
		//Cast<AGameplayHUD>(UGameplayStatics::GetGameMode(GetWorld())->HUDClass)->showScore();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->PregameStop();
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
	Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->hideScore();
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
	Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
	//}
	//else if (scorePoint != nullptr) {
	//	int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
	//	Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(score);
	//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("tochka"));
	//}

}
