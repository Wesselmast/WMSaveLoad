// Fill out your copyright notice in the Description page of Project Settings.

#include "WMSaveLoadBlueprintLibrary.h"

void UWMSaveLoadBlueprintLibrary::SaveWorld(UObject* WorldContextObject, TArray<UWMSaveLoadComponent*> Components) {
	FString Content;
	for (UWMSaveLoadComponent* SaveLoadComponent : Components) {
		if (IsValid(SaveLoadComponent)) {
			SaveLoadComponent->OnSave.Broadcast();
			Content += SaveLoadComponent->Save();
		}
	}
	FString Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/WMSaveFile.txt");
	FFileHelper::SaveStringToFile(Content, *Path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void UWMSaveLoadBlueprintLibrary::LoadWorld(UObject * WorldContextObject, TArray<UWMSaveLoadComponent*> Components) {
	TArray<FString> Result;
	FString Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/WMSaveFile.txt");
	bool Check = FFileHelper::LoadFileToStringArray(Result, *Path);

	if (!Check || !Result.IsValidIndex(0)) {
		for (UWMSaveLoadComponent* SaveLoadComponent : Components) {
			SaveLoadComponent->OnLoad.Broadcast(false);
		}
		return;
	}
	UWMSaveLoadComponent* CurrentComponent = nullptr;
	for (FString Line : Result) {
		if (Line.Contains("Object|")) {
			for (UWMSaveLoadComponent* SaveLoadComponent : Components) {
				if (Line.Contains(SaveLoadComponent->GetOwner()->GetName())) {
					CurrentComponent = SaveLoadComponent;
					break;
				}
			}
		}
		else {
			if (CurrentComponent) {
				TArray<FString> Temp;
				Line.ParseIntoArray(Temp, TEXT("|"));
				CurrentComponent->Load(Temp);
			}
		}
	}
	for (UWMSaveLoadComponent* SaveLoadComponent : Components) {
		SaveLoadComponent->OnLoad.Broadcast(true);
	}
}

void UWMSaveLoadBlueprintLibrary::DeleteWorld(UObject * WorldContextObject) {
	FString Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/WMSaveFile.txt");
	FFileHelper::SaveStringToFile("", *Path);
}
