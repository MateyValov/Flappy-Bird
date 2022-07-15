// Fill out your copyright notice in the Description page of Project Settings.


#include "Flappy.h"
#include "Components/StaticMeshComponent.h"
#include "GameplayModeBase.h"
#include "GameplayHUD.h"
#include "Obstacle.h"
#include "ScoreBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlappy::AFlappy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	hitbox->SetupAttachment(mesh);
	hitbox->OnComponentBeginOverlap.AddDynamic(this, &AFlappy::die);
	
}

// Called when the game starts or when spawned
void AFlappy::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(this, 0)->SetPause(false);
	if (cameraController != nullptr) {
		cameraController->JumpDelegate.BindUFunction(this, FName("jump"));
	}
}

void AFlappy::jump()
{
	if (!pressed) {
		currGravity = gravity;
		StartDelegate.ExecuteIfBound();
		pressed = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("castvame"));
		//Cast<AGameplayHUD>(UGameplayStatics::GetGameMode(GetWorld())->HUDClass)->showScore();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->PregameStop();
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showScore();
	}
	verticalVelocity = jumpForce;
}

void AFlappy::die(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AObstacle* obst = Cast<AObstacle>(OtherActor);
	AScoreBox* scorePoint = Cast<AScoreBox>(OtherActor);
	if (obst != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Some debug message!"));
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->hideScore();
		UGameplayStatics::GetPlayerController(this, 0)->SetPause(true);
		Cast<AGameplayHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->showEnd();
	}
	else if (scorePoint != nullptr) {
		int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore()+1;
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(score);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("tochka"));
	}
	

}

// Called every frame
void AFlappy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	verticalVelocity -= currGravity * DeltaTime;
	FVector newLocation = GetActorLocation();
	newLocation.Z += verticalVelocity;
	SetActorLocation(newLocation);
	//UGameplayStatics::GetGameMode(GetWorld())->speed;

}



