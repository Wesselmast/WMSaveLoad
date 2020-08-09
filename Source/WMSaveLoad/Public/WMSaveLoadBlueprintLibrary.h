// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "WMSaveLoadComponent.h"
#include "WMSaveLoadBlueprintLibrary.generated.h"

/**
 * 
 */

UCLASS()
class WMSAVELOAD_API UWMSaveLoadBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WMSaveLoad", meta = (WorldContext = "WorldContextObject"))
	static void SaveWorld(UObject* WorldContextObject, TArray<UWMSaveLoadComponent*> Components);

	UFUNCTION(BlueprintCallable, Category = "WMSaveLoad", meta = (WorldContext = "WorldContextObject"))
	static void LoadWorld(UObject* WorldContextObject, TArray<UWMSaveLoadComponent*> Components);

	UFUNCTION(BlueprintCallable, Category = "WMSaveLoad", meta = (WorldContext = "WorldContextObject"))
	static void DeleteWorld(UObject* WorldContextObject);
};