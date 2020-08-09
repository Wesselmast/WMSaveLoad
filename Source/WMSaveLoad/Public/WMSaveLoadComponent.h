// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "WMSaveLoadComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoad, bool, bHasSavedFile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSave);

UENUM()
enum class ESaveType : uint8 {
	INT,
	FLOAT,
	BOOL
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class WMSAVELOAD_API UWMSaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWMSaveLoadComponent();
public:	
	FString Save();
	void Load(TArray<FString> Values);
public:
	UPROPERTY(BlueprintAssignable)
	FOnLoad OnLoad;
	UPROPERTY(BlueprintAssignable)
	FOnSave OnSave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WMSaveLoad")
	TMap<FString, ESaveType> VariablesToSave;
private:
	bool GetFloatByName(FName Name, float& Float);
	bool GetBoolByName(FName Name, bool& Bool);
	bool GetIntByName(FName Name, int32& Int);

	bool SetFloatByName(FName Name, float NewFloat);
	bool SetBoolByName(FName Name, bool NewBool);
	bool SetIntByName(FName Name, int32 NewInt);
};
