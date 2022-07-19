#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GapObstacle.generated.h"


UCLASS()
class FLAPPYBIRD_API AGapObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGapObstacle();
	UFUNCTION()
		void Init(float givenSpeed);
protected:
	//float speed;
	UPROPERTY(EditAnywhere)
		class USceneComponent* root = nullptr;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshbottom = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitboxbottom = nullptr;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshtop = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* hitboxtop = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* score = nullptr;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* movement = nullptr;
	// Called when the game starts or when spawned

	UFUNCTION()
		void kill1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void kill2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void scoreUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame


};

