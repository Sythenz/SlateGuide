// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ModalWindowCommands.h"

#define LOCTEXT_NAMESPACE "FModalWindowCommandModule"

void FModalWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Slate Guide Modal Window", "Bring up Slate Guide Modal Window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
