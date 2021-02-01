// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Property.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace Str
	{
		CSCORE_API CS_DEFINE_CACHED_STRING(InputActionMap, "UCsDeveloperSettings::InputActionMap");
		CSCORE_API CS_DEFINE_CACHED_STRING(GameEvent, "UCsDeveloperSettings::GameEvent");
		CSCORE_API CS_DEFINE_CACHED_STRING(FX, "UCsDeveloperSettings::FX");
		CSCORE_API CS_DEFINE_CACHED_STRING(Sound, "UCsDeveloperSettings::Sound");
		CSCORE_API CS_DEFINE_CACHED_STRING(SkeletalMeshActor, "UCsDeveloperSettings::SkeletalMeshActor");
	}
}

#pragma endregion Cached

UCsDeveloperSettings::UCsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UObject* UCsDeveloperSettings::SafeLoadDataRootSet(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	if (!SoftPath.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);
		return nullptr;
	}

	UClass* Class = DataRootSet.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
		return nullptr;
	}
	return DOb;
}

#if WITH_EDITOR

void UCsDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsDeveloperSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyFName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FString PropertyName	   = (e.Property != NULL) ? e.Property->GetName() : TEXT("");
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;

	typedef NCsProperty::FLibrary PropertyLibrary;

	TSet<FString> PropertyNames;
	PropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

	typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;

	// Input
	{
		// ECsInputActionMap
		if (PropertyName == TEXT("ECsInputActionMap"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsInputActionMap_Internal, ECsInputActionMap, EMCsInputActionMap::Get().GetEnumName());
		}
		// ECsGameEvent
		if (PropertyName == TEXT("ECsGameEvent"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsGameEvent_Internal, ECsGameEvent, EMCsGameEvent::Get().GetEnumName());
		}
		// Input
		if (PropertyNames.Contains("Input"))
		{
			Input.OnPostEditChange(PropertyName, PropertyNames);
		}
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR