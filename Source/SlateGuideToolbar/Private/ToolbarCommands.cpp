// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ToolbarCommands.h"

#define LOCTEXT_NAMESPACE "FToolbarModule"

void FToolbarCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Toolbar", "Execute Toolbar action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
