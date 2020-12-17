// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SlateGuideDetailsViewSettings.generated.h"


/*
*
*/
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class USlateGuideDetailsViewSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Example parameters")
	TArray<FString> StringArray;

	UPROPERTY(EditAnywhere, Category = "Example parameters")
	float ExampleFloat;
};
