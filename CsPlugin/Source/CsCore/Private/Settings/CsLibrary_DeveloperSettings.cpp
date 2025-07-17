
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_DeveloperSettings.h"

// Library
#include "SourceControl/Tool/CsLibrary_SourceControlTool.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsCore, NSettings, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCore::NSettings::FLibrary, TryUpdateDefaultConfigFile)
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsCore
{
	namespace NSettings
	{
		UCsDeveloperSettings* FLibrary::Get() { return GetMutableDefault<UCsDeveloperSettings>(); }

		bool FLibrary::TryUpdateDefaultConfigFile() 
		{ 
			CS_SET_CONTEXT_AS_FUNCTION_NAME(TryUpdateDefaultConfigFile);

		#if WITH_EDITOR
			CsSourceControlToolLibrary::CheckOutFileChecked(Context, Get()->GetDefaultConfigFilename(), false);

			return Get()->TryUpdateDefaultConfigFile();
		#else
			return false;
		#endif // #if WITH_EDITOR
		}

		// Enum
		#pragma region
		
		TMap<FName, FCsEnumStructLayoutHistory>& FLibrary::GetEnumStructlayoutHistoryMap() { return Get()->EnumStructlayoutHistoryMap; }

		#pragma endregion Enum

		// Input
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_InputActionMap()	{ return Get()->GetSettingsEnum<FECsInputActionMap>(); }
		const FString& FLibrary::GetSettingsEnumPath_InputActionMap()				{ return NCsDeveloperSettings::NCached::Str::InputActionMap; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_GameEvent()		{ return Get()->GetSettingsEnum<FECsGameEvent>(); }
		const FString& FLibrary::GetSettingsEnumPath_GameEvent()					{ return NCsDeveloperSettings::NCached::Str::GameEvent; }

		#pragma endregion Input

		// Anim
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::GetVertexAnimNotify_PopulateEnumMapMethod()	{ return Get()->ECsVertexAnimNotify_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_VertexAnimNotify()			{ return Get()->GetSettingsEnum<FECsVertexAnimNotify>(); }
		const FString& FLibrary::GetSettingsEnumPath_VertexAnimNotify()							{ return NCsDeveloperSettings::NCached::Str::VertexAnimNotify; }

		#pragma endregion Anim
	}
}