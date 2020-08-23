// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExampleSettings.generated.h"


/*
*
*/
UCLASS(config = PlacementMode, defaultconfig)
class UExampleSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, config, Category = "Example parameters")
	TArray<FString> StringArray;

	UPROPERTY(EditAnywhere, config, Category = "Example parameters")
	float ExampleFloat;
};
