// Fill out your copyright notice in the Description page of Project Settings.


#include "SNotificationsWidget.h"
#include "SlateOptMacros.h"
#include <SBorder.h>
#include <EditorStyleSet.h>
#include <SBoxPanel.h>
#include "SlateGuideModalWindow.h"
#include <SButton.h>
#include <STextBlock.h>
#include <NotificationManager.h>
#include <SNotificationList.h>

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


#define LOCTEXT_NAMESPACE "FSlateGuideModalWindowModule"

void SNotificationsWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(FMargin(4.0f))
		[

			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.0f, 0.0f, 2.0f, 0.0f))
				.AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(FMargin(1.0f))
					.OnClicked(this, &SNotificationsWidget::OnCreateModalWindowNotificationInfo)
					.Text(LOCTEXT("CreateNotification", "Create Notification Info"))
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(0.0f, 0.0f, 2.0f, 0.0f))
				.AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(FMargin(1.0f))
					.OnClicked(this, &SNotificationsWidget::OnCreateModalWindowNotificationWithButtons)
					.Text(LOCTEXT("CreateNotificationWithButton", "Create Notification With Buttons"))
				]
			]
		]
	];
	
}

FReply SNotificationsWidget::OnCreateModalWindowNotificationInfo()
{
	const FText NotificationText = LOCTEXT("SlateGuideCreateNotificationInfo", "Everybody wants to be a cat!");

	FNotificationInfo Info(NotificationText);
	Info.ExpireDuration = 2.0f;

	//Display a different info icon than default warning
	Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Note"));

	FSlateNotificationManager::Get().AddNotification(Info);

	return FReply::Handled();
}

FReply SNotificationsWidget::OnCreateModalWindowNotificationWithButtons()
{
	const FText NotificationText = LOCTEXT("SlateGuideCreateNotificationButtons", "Why should you be first?");

	TSharedPtr<SNotificationItem> NotificationPin = NotificationPtr.Pin();
	if (NotificationPin.IsValid())
	{
		return FReply::Handled();
	}

	FNotificationInfo Info(NotificationText);

	// Add the buttons with text, tooltip and callback
	Info.ButtonDetails.Add(FNotificationButtonInfo(
		LOCTEXT("RestartNow", "Because I'm a lady. That's why."),
		LOCTEXT("RestartNowToolTip", "Because I'm a lady. That's why."),
		FSimpleDelegate::CreateRaw(this, &SNotificationsWidget::OnNotificationAcceptClicked))
	);
	Info.ButtonDetails.Add(FNotificationButtonInfo(
		LOCTEXT("RestartLater", "You're nothing but a sister."),
		LOCTEXT("RestartLaterToolTip", "You're nothing but a sister."),
		FSimpleDelegate::CreateRaw(this, &SNotificationsWidget::OnNotificationDismissClicked))
	);

	//Display a different info icon than default warning
	Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));

	// We will be keeping track of this ourselves
	Info.bFireAndForget = false;

	// Set the width so that the notification doesn't resize as its text changes
	Info.WidthOverride = 400.0f;

	Info.bUseLargeFont = false;
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = false;

	// Launch notification
	NotificationPtr = FSlateNotificationManager::Get().AddNotification(Info);
	NotificationPin = NotificationPtr.Pin();

	if (NotificationPin.IsValid())
	{
		NotificationPin->SetCompletionState(SNotificationItem::CS_Pending);
	}
	return FReply::Handled();
}

void SNotificationsWidget::OnNotificationAcceptClicked()
{
	TSharedPtr<SNotificationItem> NotificationPin = NotificationPtr.Pin();
	if (NotificationPin.IsValid())
	{
		NotificationPin->SetText(LOCTEXT("RestartingNow", "You can do a thing here, SNotificationsWidget::OnNotificationAcceptClicked()"));
		NotificationPin->SetCompletionState(SNotificationItem::CS_Success);
		NotificationPin->ExpireAndFadeout();
		NotificationPtr.Reset();
	}
	
	//Do thing here...
}

void SNotificationsWidget::OnNotificationDismissClicked()
{
	TSharedPtr<SNotificationItem> NotificationPin = NotificationPtr.Pin();
	if (NotificationPin.IsValid())
	{
		NotificationPin->SetText(LOCTEXT("RestartDismissed", "Dismissed..."));
		NotificationPin->SetCompletionState(SNotificationItem::CS_None);
		NotificationPin->ExpireAndFadeout();
		NotificationPtr.Reset();
	}
}


#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
