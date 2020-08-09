// Fill out your copyright notice in the Description page of Project Settings.


#include "WMSaveLoadComponent.h"

UWMSaveLoadComponent::UWMSaveLoadComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

FString UWMSaveLoadComponent::Save() {
	FString Content = TEXT("Object|") + GetOwner()->GetName() + "\n";

	for (TPair<FString, ESaveType>& Elem : VariablesToSave) {
		switch(Elem.Value) {
			case ESaveType::BOOL: {
				bool Temp;
				if (GetBoolByName(FName(*Elem.Key), Temp)) {
					Content += TEXT("Bool|") + Elem.Key + TEXT("|") + (Temp ? TEXT("True") : TEXT("False")) + "\n";
				}
			}
			case ESaveType::FLOAT: {
				float Temp;
				if(GetFloatByName(FName(*Elem.Key), Temp)) {
					Content += TEXT("Float|") + Elem.Key + TEXT("|") + FString::SanitizeFloat(Temp) + "\n";
				}
			}
			case ESaveType::INT: {
				int Temp;
				if(GetIntByName(FName(*Elem.Key), Temp)) {
					Content += TEXT("Int|") + Elem.Key + TEXT("|") + FString::FromInt(Temp) + "\n";
				}
			}
		}
	}
	return Content;
}

void UWMSaveLoadComponent::Load(TArray<FString> Values) {
	AActor* Actor = GetOwner();

	if (Values[0] == TEXT("Bool"))  SetBoolByName(FName(*Values[1]), Values[2].ToBool());
	if (Values[0] == TEXT("Float")) SetFloatByName(FName(*Values[1]), FCString::Atof(*Values[2]));
	if (Values[0] == TEXT("Int"))   SetIntByName(FName(*Values[1]), FCString::Atoi(*Values[2]));
}

bool UWMSaveLoadComponent::GetFloatByName(FName Name, float & Float) {
	UFloatProperty* FloatProperty = FindField<UFloatProperty>(GetOwner()->GetClass(), Name);
	if (FloatProperty != nullptr) {
		Float = FloatProperty->GetPropertyValue_InContainer(GetOwner());
		return true;
	}
	return false;
}

bool UWMSaveLoadComponent::GetBoolByName(FName Name, bool & Bool) {
	UBoolProperty* BoolProperty = FindField<UBoolProperty>(GetOwner()->GetClass(), Name);
	if (BoolProperty != nullptr) {
		Bool = BoolProperty->GetPropertyValue_InContainer(GetOwner());
		return true;
	}
	return false;
}

bool UWMSaveLoadComponent::GetIntByName(FName Name, int32 & Int) {
	UIntProperty* IntProperty = FindField<UIntProperty>(GetOwner()->GetClass(), Name);
	if (IntProperty != nullptr) {
		Int = IntProperty->GetPropertyValue_InContainer(GetOwner());
		return true;
	}
	return false;
}

bool UWMSaveLoadComponent::SetFloatByName(FName Name, float NewFloat) {
	UFloatProperty* FloatProperty = FindField<UFloatProperty>(GetOwner()->GetClass(), Name);
	if (FloatProperty != nullptr) {
		FloatProperty->SetPropertyValue_InContainer(GetOwner(), NewFloat);
		return true;
	}
	return false;
}

bool UWMSaveLoadComponent::SetBoolByName(FName Name, bool NewBool) {
	UBoolProperty* BoolProperty = FindField<UBoolProperty>(GetOwner()->GetClass(), Name);
	if (BoolProperty != nullptr) {
		BoolProperty->SetPropertyValue_InContainer(GetOwner(), NewBool);
		return true;
	}
	return false;
}

bool UWMSaveLoadComponent::SetIntByName(FName Name, int32 NewInt) {
	UIntProperty* IntProperty = FindField<UIntProperty>(GetOwner()->GetClass(), Name);
	if (IntProperty != nullptr) {
		IntProperty->SetPropertyValue_InContainer(GetOwner(), NewInt);
		return true;
	}
	return false;
}