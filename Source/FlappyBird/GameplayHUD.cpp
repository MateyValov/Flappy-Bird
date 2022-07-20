// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "HighScore.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	//showMenu();
	PregameStart();
}

void AGameplayHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (GEngine && GEngine->GameViewport && (EndWidgetConteiner.IsValid() || PregameWidgetConteiner.IsValid())) {
	//	return;
	//}
	/*if (GEngine && GEngine->GameViewport && PregameWidgetConteiner.IsValid()) {
		return;
	}*/
	//hideScore();
	//showScore();
}

void AGameplayHUD::showEnd()
{
	clear();
	int HighScore = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->HighScore;
	int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore();

	if (HighScore < score) {
		UHighScore* SaveGameInstance = Cast<UHighScore>(UGameplayStatics::CreateSaveGameObject(UHighScore::StaticClass()));
		SaveGameInstance->HighScore = score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance,"HighScore", 0);
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->UpdateHighScore();
	}
	
	CurrentWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), EndWidgetClass);
	if (PlayerOwner && CurrentWidget) {
		CurrentWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}


void AGameplayHUD::showScore()
{
	clear();
	CurrentWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), ScoreWidgetClass);
	if (PlayerOwner && CurrentWidget) {
		CurrentWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}

}


void AGameplayHUD::PregameStart()
{
	clear();
	CurrentWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), PregameWidgetClass);
	if (PlayerOwner && CurrentWidget) {
		CurrentWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}


void AGameplayHUD::clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}


