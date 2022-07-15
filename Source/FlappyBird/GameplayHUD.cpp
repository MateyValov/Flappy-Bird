// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "SScoreWidget.h"
#include "SDeathScreenWidget.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "HighScore.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SPregameWidget.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	//showMenu();
	PregameStart();
}

void AGameplayHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine && GEngine->GameViewport && (EndWidgetConteiner.IsValid() || PregameWidgetConteiner.IsValid())) {
		return;
	}
	/*if (GEngine && GEngine->GameViewport && PregameWidgetConteiner.IsValid()) {
		return;
	}*/
	hideScore();
	showScore();
}

void AGameplayHUD::showEnd()
{
	int HighScore = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->HighScore;
	int score = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetScore();

	if (HighScore < score) {
		//int neshto = 1 + SaveGameInstance->HighScore;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::FromInt(neshto));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(LoadedGame->HighScore));
		UHighScore* SaveGameInstance = Cast<UHighScore>(UGameplayStatics::CreateSaveGameObject(UHighScore::StaticClass()));
		SaveGameInstance->HighScore = score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance,"HighScore", 0);
		Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->UpdateHighScore();
	}
	if (GEngine && GEngine->GameViewport) {
		EndWidget = SNew(SDeathScreenWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(EndWidgetConteiner, SWeakWidget).PossiblyNullContent(EndWidget.ToSharedRef()));
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}

	}

}

void AGameplayHUD::hideEnd()
{
	if (GEngine && GEngine->GameViewport && EndWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(EndWidgetConteiner.ToSharedRef());
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AGameplayHUD::showScore()
{
	//PregameStop();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("showvame score"));
	if (GEngine && GEngine->GameViewport) {
		ScoreWidget = SNew(SScoreWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(ScoreWidgetConteiner, SWeakWidget).PossiblyNullContent(ScoreWidget.ToSharedRef()));
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("scora se vijda"));
	}

}

void AGameplayHUD::hideScore()
{
	if (GEngine && GEngine->GameViewport && ScoreWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(ScoreWidgetConteiner.ToSharedRef());
	}
}

void AGameplayHUD::PregameStart()
{
	if (GEngine && GEngine->GameViewport) {
		PregameWidget = SNew(SPregameWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(PregameWidgetConteiner, SWeakWidget).PossiblyNullContent(PregameWidget.ToSharedRef()));
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("scora se vijda"));
	}
}

void AGameplayHUD::PregameStop()
{
	if (GEngine && GEngine->GameViewport && PregameWidgetConteiner.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(PregameWidgetConteiner.ToSharedRef());
		PregameWidgetConteiner = nullptr;
	}
}


