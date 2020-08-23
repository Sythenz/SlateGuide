// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SlateGuideModeCategory.h"

#include "LevelEditor.h"
#include <Settings/Public/ISettingsModule.h>
#include <Settings/Public/ISettingsContainer.h>
#include <Settings/Public/ISettingsSection.h>
#include <PlacementMode/Public/IPlacementModeModule.h>

static const FName SettingsTabName("Settings");

#define LOCTEXT_NAMESPACE "FSlateGuideModeCategoryModule"

void FSlateGuideModeCategoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//Create a category
	FPlacementCategoryInfo Info(
		FText::FromString(TEXT("Example Category")),
		TEXT("ExampleCategory"),
		TEXT("Example Category"),
		0,
		false
	);

	//Register the Category
	IPlacementModeModule::Get().RegisterPlacementCategory(Info);
	
	//Add a static class to our new example category
	IPlacementModeModule::Get().RegisterPlaceableItem(FName(TEXT("ExampleCategory")), MakeShareable(new FPlaceableItem(nullptr, FAssetData(AActor::StaticClass()))));
}

void FSlateGuideModeCategoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateGuideModeCategoryModule, SlateGuideModeCategory)