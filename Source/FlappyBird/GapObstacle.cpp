
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

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	//bottom
	meshbottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBottom"));
	meshbottom->SetupAttachment(root);
	meshbottom->SetStaticMesh(MeshObj.Object);
	meshbottom->SetRelativeScale3D(FVector(0.8, 0.8, 6));
	meshbottom->SetRelativeLocation(FVector(0, 0, -220));

	hitboxbottom = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxBottom"));
	hitboxbottom->SetupAttachment(meshbottom);
	hitboxbottom->SetRelativeScale3D(FVector(1.42, 1.42, 1.58));
	hitboxbottom->OnComponentBeginOverlap.AddDynamic(this, &AGapObstacle::kill1);

	//top
	meshtop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshTop"));
	meshtop->SetupAttachment(root);
	meshtop->SetStaticMesh(MeshObj.Object);
	meshtop->SetRelativeScale3D(FVector(0.8, 0.8, 6));
	meshtop->SetRelativeLocation(FVector(0, 0, 640));

	hitboxtop = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxTop"));
	hitboxtop->SetupAttachment(meshtop);
	hitboxtop->SetRelativeScale3D(FVector(1.42, 1.42, 1.58));
	hitboxtop->OnComponentBeginOverlap.AddDynamic(this, &AGapObstacle::kill2);

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
		bird->die();
	}
}

void AGapObstacle::kill2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		bird->die();
	}
	
}
void AGapObstacle::scoreUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT(""));
	ABird* bird = Cast<ABird>(OtherActor);
	if (bird != nullptr) {
		int points = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore() + 1;
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore(points);
		return;
	}
	AObstacleGenerator* gen = Cast<AObstacleGenerator>(OtherActor);
	if (gen != nullptr) {
		Destroy();
	}
}



