// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SlateGuideSettings.h"

#include "LevelEditor.h"
#include "ExampleSettings.h"
#include <Settings/Public/ISettingsModule.h>
#include <Settings/Public/ISettingsContainer.h>
#include <Settings/Public/ISettingsSection.h>

static const FName SettingsTabName("Settings");

#define LOCTEXT_NAMESPACE "FSlateGuideSettingsModule"

void FSlateGuideSettingsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterSettings();
	
}

void FSlateGuideSettingsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

void FSlateGuideSettingsModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("Example Settings",
			LOCTEXT("RuntimeWDCategoryName", "ExampleCategory"),
			LOCTEXT("RuntimeWDCategoryDescription", "Example Category from Slate Guide"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "ExampleCategory", "ExampleSettings",
			LOCTEXT("RuntimeGeneralSettingsName", "Example Settings"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "An example settings panel from Slate Guide."),
			GetMutableDefault<UExampleSettings>()
		);

		if (SettingsSection.IsValid())
		{
			//Bind to On Modified (Called every time a setting is changed and saved)
			SettingsSection->OnModified().BindRaw(this, &FSlateGuideSettingsModule::HandleSettingsSaved);
		}
	}
}

void FSlateGuideSettingsModule::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "ExampleCategory", "ExampleSettings");
	}
}

bool FSlateGuideSettingsModule::HandleSettingsSaved()
{
	UExampleSettings* Settings = GetMutableDefault<UExampleSettings>();
	bool ResaveSettings = false;

	Settings->SaveConfig();

	//Validate any settings here. This gets called every time a setting gets changed.
	//You can get any setting from the above mutable default.
	
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateGuideSettingsModule, SlateGuideSettings)