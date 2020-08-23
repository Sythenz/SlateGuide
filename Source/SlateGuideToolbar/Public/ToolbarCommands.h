// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ToolbarStyle.h"

class FToolbarCommands : public TCommands<FToolbarCommands>
{
public:

	FToolbarCommands()
		: TCommands<FToolbarCommands>(TEXT("Toolbar"), NSLOCTEXT("Contexts", "Toolbar", "Toolbar Plugin"), NAME_None, FToolbarStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
