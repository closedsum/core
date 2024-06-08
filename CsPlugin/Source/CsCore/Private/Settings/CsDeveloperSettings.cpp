// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

#if WITH_EDITOR
// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/ProjectPackagingSettings.h"
// Interface
#include "Types/Enum/Tool/CsGetEnumStructTool.h"
// UI
//#include "Framework/Application/SlateApplication.h"
// Editor
#include "PackageTools.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsDeveloperSettings)

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace NCached
	{
		namespace Str
		{
			// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDeveloperSettings, PopulateAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDeveloperSettings, PostEditChangeChainProperty);

			CSCORE_API CS_DEFINE_CACHED_STRING(InputActionMap, "UCsDeveloperSettings::InputActionMap");
			CSCORE_API CS_DEFINE_CACHED_STRING(GameEvent, "UCsDeveloperSettings::GameEvent");
			CSCORE_API CS_DEFINE_CACHED_STRING(Sound, "UCsDeveloperSettings::Sound");
			CSCORE_API CS_DEFINE_CACHED_STRING(StaticMeshActor, "UCsDeveloperSettings::StaticMeshActor");
			CSCORE_API CS_DEFINE_CACHED_STRING(SkeletalMeshActor, "UCsDeveloperSettings::SkeletalMeshActor");
			CSCORE_API CS_DEFINE_CACHED_STRING(VertexAnimNotify, "UCsDeveloperSettings::VertexAnimNotify");
		}
	}
}

#pragma endregion Cached

UCsDeveloperSettings::UCsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Enum
	EnumStructlayoutHistoryMap(),
	bEnumStructLayoutResolveChanges(false),
	bForceEnumStructLayoutResolveChanges(false),
	// Input
	InputSystem(ECsInputSystem::Default),
	Input(),
	EnhancedInput(),
	Manager_Input(),
	// Script
	bEnableScriptChecked(false)
{
}

// Script
#pragma region

#if WITH_EDITOR

void UCsDeveloperSettings::ApplyEnableScriptChecked()
{
	CsCVarEnableScriptChecked->Set(bEnableScriptChecked, ECVF_SetByConsole);
}

#endif // #if WITH_EDITOR

#pragma endregion Script

#if WITH_EDITOR

void UCsDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// bEnumStructLayoutResolveChanges
	if (PropertyName == FName("bEnumStructLayoutResolveChanges"))
	{
		if (ICsGetEnumStructTool* GetEnumStructTool = Cast<ICsGetEnumStructTool>(GEngine))
		{
			GetEnumStructTool->GetEnumStructTool().ResolveLayoutChangesImpl(false);
		}
		bEnumStructLayoutResolveChanges = false;
	}
	// bForceEnumStructLayoutResolveChanges
	if (PropertyName == FName("bForceEnumStructLayoutResolveChanges"))
	{
		if (ICsGetEnumStructTool* GetEnumStructTool = Cast<ICsGetEnumStructTool>(GEngine))
		{
			GetEnumStructTool->GetEnumStructTool().ResolveLayoutChangesImpl(true);
		}
		bForceEnumStructLayoutResolveChanges = false;
	}
	// bEnableScriptChecked
	if (PropertyName == FName("bEnableScriptChecked"))
	{
		ApplyEnableScriptChecked();
	}
	Super::PostEditChangeProperty(e);
}

void UCsDeveloperSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	using namespace NCsDeveloperSettings::NCached;

	const FString& Context = Str::PostEditChangeChainProperty;

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
			TryUpdateDefaultConfigFile();
		}
		// ECsGameEvent
		if (PropertyName == TEXT("ECsGameEvent"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsGameEvent_Internal, ECsGameEvent, EMCsGameEvent::Get().GetEnumName());
			TryUpdateDefaultConfigFile();
		}
		// Input
		if (PropertyNames.Contains("Input"))
		{
			Input.OnPostEditChange(PropertyName, PropertyNames);
		}
	}
	// PIE
	{
		if (PropertyNames.Contains("PIE") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			PIE.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("PIE_Mobile") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			PIE_Mobile.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("Standalone") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			Standalone.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("Standalone_Mobile") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			Standalone_Mobile.SwapViewportDimensions();
		}
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR