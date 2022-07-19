// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidget(TEXT("/Game/Blueprints/MainMenuWidget.MainMenuWidget_C"));
	if (!ensure(MainMenuWidget.Class != nullptr)) return;
	
	MenuMenuWidgetClass = MainMenuWidget.Class;
	
	showMenu();
}

void AMenuHUD::showMenu()
{
	
	MenuWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MenuMenuWidgetClass);
	if (PlayerOwner){
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
	/*if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMenuCompoundWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetConteiner, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
		
	
	}*/

}

void AMenuHUD::hideMenu()
{
	//if (GEngine && GEngine->GameViewport && MenuWidgetConteiner.IsValid()) {
		//GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetConteiner.ToSharedRef());
	//mainWidge->RemoveFromViewport();
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	//}
}
