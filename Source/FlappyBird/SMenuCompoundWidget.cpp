// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuCompoundWidget.h"
#include "Widgets/Images/SImage.h"
#include "MenuHUD.h"
#include "Engine/World.h"
//#include "Kismet/GameplayStatics.h"
#include "SlateOptMacros.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "MainMenu"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMenuCompoundWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);
	const FText TitleText = LOCTEXT("GameTitle", "Flappy Bird");
	const FText PlayText = LOCTEXT("Play", "Play");
	const FText QuitText = LOCTEXT("Quit", "Quit");

	FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFont.Size = 60.0f;
	FSlateFontInfo ButtonFont = TitleFont;
	ButtonFont.Size = 40.0f;

	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay) 
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
			[
				SNew(SImage).ColorAndOpacity(FColor::Black)
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[	//Title
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleFont)
					.Text(TitleText)
					.Justification(ETextJustify::Center)
				]
				//PLay Button
				+SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMenuCompoundWidget::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonFont)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
					
				]
				//Quit Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMenuCompoundWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonFont)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]

				]
			]
	];
	
}
FReply SMenuCompoundWidget::OnPlayClicked() const
{
	FLatentActionInfo LatentInfo;
	//UGameplayStatics::LoadStreamLevel(this, "Game", true, true, LatentInfo);
	UGameplayStatics::OpenLevel(GEngine->GetWorld(), "Game");
	OwningHUD->hideMenu();
	return FReply::Handled();
}

FReply SMenuCompoundWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* pc = OwningHUD->PlayerOwner) {
			pc->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE