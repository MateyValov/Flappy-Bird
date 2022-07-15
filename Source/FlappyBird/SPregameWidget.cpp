// Fill out your copyright notice in the Description page of Project Settings.


#include "SPregameWidget.h"
#include "SlateOptMacros.h"
#include "GameplayHUD.h"
//#include "GameplayModeBase.h"
//#include "Kismet/GameplayStatics.h"
#define LOCTEXT_NAMESPACE "Pregame"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPregameWidget::Construct(const FArguments& InArgs)
{
	const FMargin ContentPadding = FMargin(500.0f, 505.0f);
	const FText TitleText = LOCTEXT("Tutorial", "Press Jump to Start");
	FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFont.Size = 50.0f;
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(TitleFont)
				.Text(TitleText)
				.Justification(ETextJustify::Center)
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE