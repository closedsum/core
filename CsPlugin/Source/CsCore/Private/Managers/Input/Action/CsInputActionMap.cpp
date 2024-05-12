// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Action/CsInputActionMap.h"

// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsInputActionMap)

namespace NCsInputActionMap
{
	namespace NCached
	{
		namespace Str
		{
			const FString ConditionalAddLayout = TEXT("NCsInputActionMap::ConditionalAddLayout");

			const FString InputActionMap = TEXT("InputActionMap");
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsInputActionMap::NCached;

		EMCsInputActionMap::Get().ClearUserDefinedEnums();

		typedef NCsCore::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_InputActionMap();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_InputActionMap();
		Payload.EnumName				 = Str::InputActionMap;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &FCsLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	#define LayoutLibrary NCsEnum::NStruct::NLayout::FLibrary

	void ConditionalAddLayout()
	{
		using namespace NCsInputActionMap::NCached;

		const FString& Context = Str::ConditionalAddLayout;

		FName EnumName;
		TArray<FName> Names;
		GetNames(EnumName, Names);
		LayoutLibrary::ConditionalAddLayout(EnumName, Names, nullptr);
	}

	void AddPropertyChange()
	{
		ConditionalAddLayout();
		LayoutLibrary::AddPropertyChange(EMCsInputActionMap::Get().GetEnumFName(), FECsInputActionMap::StaticStruct());
	}

	#undef LayoutLibrary
}