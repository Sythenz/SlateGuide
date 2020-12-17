// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SlateGuideModalWindow.h"
#include "ModalWindowStyle.h"
#include "ModalWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include <Widgets/Input/SButton.h>
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include <EditorStyleSet.h>

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
	FText ExampleText = LOCTEXT("ExampleWidgetText", "Slate Guide Examples");

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
				.MaxHeight(32.0f)
				.Padding(FMargin(10.0f))
				[
					SNew(STextBlock)
					.Text(ExampleText)
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 18))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FMargin(4.0f))
				[
					SAssignNew(BasicWidget, SBasicWidget)
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.MaxHeight(32.0f)
				.Padding(FMargin(4.0f))
				[
					SAssignNew(NotificationWidget, SNotificationsWidget)
				]


			]
		];
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