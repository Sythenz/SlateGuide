// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/SBasicWidget.h"
#include "SlateOptMacros.h"
#include <EditorStyleSet.h>


#define LOCTEXT_NAMESPACE "FSlateGuideModalWindowModule"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBasicWidget::Construct(const FArguments& InArgs)
{

	ChildSlot
	[
		// Populate the widget
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(FMargin(4.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WindowWidgetText", "Here you can find examples of different types of widgets used throughout the editor.\nEach of the sections below are found in SlateGuideModalWindow/Widgets for organization."))
			]
		]		
	];
	
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
