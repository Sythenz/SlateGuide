// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATEGUIDEMODALWINDOW_API SNotificationsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNotificationsWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	//An example of creating a notification in UE4.
	FReply OnCreateModalWindowNotificationInfo();

	//An example of creating a notification with buttons in UE4.
	FReply OnCreateModalWindowNotificationWithButtons();

	/** Used to reference to the active restart notification */
	TWeakPtr<SNotificationItem> NotificationPtr;

	void OnNotificationAcceptClicked();
	void OnNotificationDismissClicked();
};
