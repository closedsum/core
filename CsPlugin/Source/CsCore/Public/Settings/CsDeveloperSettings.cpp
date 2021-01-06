// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

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