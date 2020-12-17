// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SBasicWidget.h"
#include "Widgets/SNotificationsWidget.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSlateGuideModalWindowModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class SBasicWidget> BasicWidget;
	TSharedPtr<class SNotificationsWidget> NotificationWidget;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
