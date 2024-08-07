
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_DeveloperSettings.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Interface
#include "SourceControl/Tool/CsGetSourceControlTool.h"

namespace NCsCore
{
	namespace NSettings
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCore::NSettings::FLibrary, TryUpdateDefaultConfigFile);
				}
			}
		}

		UCsDeveloperSettings* FLibrary::Get() { return GetMutableDefault<UCsDeveloperSettings>(); }

		#define USING_NS_CACHED using namespace NCsCore::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsCore::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		bool FLibrary::TryUpdateDefaultConfigFile() 
		{ 
			SET_CONTEXT(TryUpdateDefaultConfigFile);

		#if WITH_EDITOR
			typedef NCsSourceControl::NTool::FImpl SourceControlToolType;

			ICsGetSourceControlTool* GetSourceControlTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetSourceControlTool);
			SourceControlToolType* SourceControlTool	  = GetSourceControlTool->GetSourceControlTool(); 
			
			SourceControlTool->CheckOutFileImpl(Get()->GetDefaultConfigFilename(), false);

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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}