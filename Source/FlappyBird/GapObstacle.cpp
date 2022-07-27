
#include "GapObstacle.h"
#include "Components/BoxComponent.h"
#include "Bird.h"
#include "GameplayModeBase.h"
#include "Engine.h"
#include "ObstacleGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AGapObstacle::AGapObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movement->ProjectileGravityScale = 0;

	//ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Meshes/Enviroment/SM_Pipe.SM_Pipe'"));
	ConstructorHelpers::FObjectFinder<UMaterial> MeshMat(TEXT("Material'/Game/Meshes/Enviroment/M_dark_green.M_dark_green'"));
	FVector scale(0.45, 0.45, 0.25);
	//bottom
	meshbottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	meshbottom->SetupAttachment(root);
	meshbottom->SetStaticMesh(MeshObj.Object);
	meshbottom->SetMaterial(0,MeshMat.Object);
	meshbottom->SetRelativeScale3D(scale);
	meshbottom->SetRelativeLocation(FVector(0, 0, -220));
	meshbottom->SetGenerateOverlapEvents(true);
	meshbottom->SetCollisionProfileName("OverlapAll");
	meshbottom->OnComponentBeginOverlap.AddDynamic(this, &AGapObstacle::kill1); 

	//top
	meshtop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshTop"));
	meshtop->SetupAttachment(root);
	meshtop->SetStaticMesh(MeshObj.Object);
	meshtop->SetMaterial(0, MeshMat.Object);
	meshtop->SetRelativeScale3D(scale);
	meshtop->SetRelativeLocation(FVector(0, 0, 640));
	meshtop->SetRelativeRotation(FRotator(180, 0, 0));
	meshtop->SetGenerateOverlapEvents(true);
	meshtop->SetCollisionProfileName("OverlapAll");
	meshtop->OnComponentBeginOverlap.AddDynamic(this, &AGapObstacle::kill2);


	//score
	score = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	score->SetupAttachment(root);
	score->SetRelativeScale3D(FVector(0.6, 0.6, 3.8));
	score->SetRelativeLocation(FVector(0, 0, 210));
	score->OnComponentBeginOverlap.AddDynamic(this, &AGapObstacle::scoreUp);
}

void AGapObstacle::Init(float givenSpeed)
{
	movement->Velocity = FVector(0, -givenSpeed, 0);
	movement->InitialSpeed = givenSpeed;
	movement->MaxSpeed = movement->InitialSpeed;
}

void AGapObstacle::kill1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("umrq"));
		bird->EndGame(bird);
	}
}

void AGapObstacle::kill2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("umrq"));

	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("umrq"));

		bird->EndGame(bird);
	}
	
}
void AGapObstacle::scoreUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("tochka"));

	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("tochka"));
		int points = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(points);
		return;
	}
	AObstacleGenerator* gen = Cast<AObstacleGenerator>(OtherActor);
	if (gen != nullptr) {
		Destroy();
	}
}



