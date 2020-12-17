// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SDetailsViewWidget.h"
#include <Widgets/SBoxPanel.h>
#include <EditorStyleSet.h>
#include "SlateOptMacros.h"
#include <Widgets/Input/SButton.h>
#include <PropertyEditorModule.h>

#define LOCTEXT_NAMESPACE "FSlateGuideModalWindowModule"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDetailsViewWidget::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;

	USlateGuideDetailsViewSettings* DetailSettings = NewObject<USlateGuideDetailsViewSettings>();

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(DetailSettings);

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		[
			DetailsView.ToSharedRef()
		]
	];
	
}

FReply SDetailsViewWidget::OnCreateDetailsView()
{

	return FReply::Handled();
}

FReply SDetailsViewWidget::OnCreateCustomSceneOutliner()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE
