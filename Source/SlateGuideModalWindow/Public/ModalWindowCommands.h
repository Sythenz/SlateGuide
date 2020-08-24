// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ModalWindowStyle.h"

class FModalWindowCommands : public TCommands<FModalWindowCommands>
{
public:

	FModalWindowCommands()
		: TCommands<FModalWindowCommands>(TEXT("SlateGuideModalWindow"), NSLOCTEXT("Contexts", "Slate Guide Modal Window", "Slate Guide Plugin"), NAME_None, FModalWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};