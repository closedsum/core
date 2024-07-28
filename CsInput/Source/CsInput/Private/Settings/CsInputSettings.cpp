// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsInputSettings.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Property.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsInputSettings)

// Cached
#pragma region

namespace NCsInputSettings
{
	namespace NCached
	{
		namespace Str
		{
			// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsInputSettings, PopulateAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsInputSettings, PostEditChangeChainProperty);

			CSINPUT_API CS_DEFINE_CACHED_STRING(InputActionMap, "UCsInputSettings::InputActionMap");
			CSINPUT_API CS_DEFINE_CACHED_STRING(GameEvent, "UCsInputSettings::GameEvent");
		}
	}
}

#pragma endregion Cached

UCsInputSettings::UCsInputSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Input
	InputSystem(ECsInputSystem::Default),
	Input(),
	EnhancedInput(),
	Manager_Input()
{
}

// UOjbect Interface
#pragma region

#if WITH_EDITOR

void UCsInputSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsInputSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	using namespace NCsInputSettings::NCached;

	const FString& Context = Str::PostEditChangeChainProperty;

	const FName PropertyFName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FString PropertyName	   = (e.Property != NULL) ? e.Property->GetName() : TEXT("");
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;

	TSet<FString> PropertyNames;
	CsPropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

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

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion UObject Interface