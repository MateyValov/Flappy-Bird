// Fill out your copyright notice in the Description page of Project Settings.


#include "SScoreWidget.h"
#include "SlateOptMacros.h"
#include "GameplayHUD.h"
#include "GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SScoreWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(50.0f, 50.0f);
	const FText ScoreText = FText::FromString(FString::FromInt(Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(OwningHUD->GetWorld()))->GetScore()));
	FSlateFontInfo ScoreFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ScoreFont.Size = 40.0f;

	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(ScoreFont)
				.Text(ScoreText)
				.Justification(ETextJustify::Right)
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
