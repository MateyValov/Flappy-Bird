// Fill out your copyright notice in the Description page of Project Settings.


#include "SDeathScreenWidget.h"
#include "Widgets/Images/SImage.h"
#include "GameplayHUD.h"
#include "SlateOptMacros.h"
//#include "GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "EndScreen"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDeathScreenWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);
	//const FText TitleText = LOCTEXT("GameTitle", "You failed");
	const FText PlayText = LOCTEXT("Play", "Play again");
	const FText QuitText = LOCTEXT("Quit", "Quit");

	FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFont.Size = 50.0f;
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
					+ SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
						.OnClicked(this, &SDeathScreenWidget::OnPlayClicked)
						[
							SNew(STextBlock)
							.Font(ButtonFont)
							.Text(PlayText)
							.Justification(ETextJustify::Center)
						]

					]
	
			]
		];
}

FReply SDeathScreenWidget::OnPlayClicked() const
{
	FLatentActionInfo LatentInfo;
	//UGameplayStatics::LoadStreamLevel(this, "Game", true, true, LatentInfo);
	Cast<AGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ResetLevel();
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE