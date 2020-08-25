// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SlateGuideModalWindow.h"
#include "ModalWindowStyle.h"
#include "ModalWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include <SButton.h>
#include <EditorStyleSet.h>

//Notification includes
#include <SNotificationList.h>
#include <NotificationManager.h>
#include <Reply.h>

static const FName StyleGuideTabName("StyleGuideModalWindow");

#define LOCTEXT_NAMESPACE "FSlateGuideModalWindowModule"

void FSlateGuideModalWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FModalWindowStyle::Initialize();
	FModalWindowStyle::ReloadTextures();

	FModalWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FModalWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSlateGuideModalWindowModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	//Register our Slate Modal Window in the Window dropdown of Unreal.
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSlateGuideModalWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	//Register our Slate Modal Window in the main toolbar beside Settings.
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSlateGuideModalWindowModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StyleGuideTabName, FOnSpawnTab::CreateRaw(this, &FSlateGuideModalWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSlateGuideTabName", "Slate Guide Modal Window"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FSlateGuideModalWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FModalWindowStyle::Shutdown();

	FModalWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StyleGuideTabName);
}

TSharedRef<SDockTab> FSlateGuideModalWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSlateGuideModalWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SlateGuideModalWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.WidthOverride(100.0f)
			.HeightOverride(300.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(0.1f)
				.Padding(FMargin(4.0f))
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
					.Padding(FMargin(4.0f))
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.FillHeight(1.0f)
						[
							SNew(STextBlock)
							.Text(WidgetText)
						]
					]
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.Padding(FMargin(4.0f))
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
					.Padding(FMargin(4.0f))
					[

						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.FillHeight(1.0f)
						[
							SNew(SButton)
							.ContentPadding(FMargin(1, 0))
							//We use OnClicked_Raw here because we're currently in a class deriving from IModuleInterface
							.OnClicked_Raw(this, &FSlateGuideModalWindowModule::OnCreateModalWindowNotificationInfo)
							[
								SNew(STextBlock)
								.Text(FText::FromString(FString(TEXT("Create NotificationInfo"))))
							]
						]
					]
				]


			]
		];
}


FReply FSlateGuideModalWindowModule::OnCreateModalWindowNotificationInfo()
{
	//An example of creating a notification in UE4.

	const FText NotificationText = LOCTEXT("SlateGuideCreateNotificationInfo", "Everybody wants to be a cat");

	FNotificationInfo Info(NotificationText);
	Info.ExpireDuration = 2.0f;
	
	FSlateNotificationManager::Get().AddNotification(Info);

	return FReply::Handled();
}


void FSlateGuideModalWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(StyleGuideTabName);
}

void FSlateGuideModalWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FModalWindowCommands::Get().OpenPluginWindow);
}

void FSlateGuideModalWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FModalWindowCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateGuideModalWindowModule, SlateGuideModalWindow)