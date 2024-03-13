
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_FXSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsFXSettings.h"
// Interface
#include "SourceControl/Tool/CsGetSourceControlTool.h"

namespace NCsFX
{
	namespace NSettings
	{
		UCsFXSettings* FLibrary::Get() { return GetMutableDefault<UCsFXSettings>(); }

		#define USING_NS_CACHED using namespace NCsFX::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsFX::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// FX
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_FX()	{ return Get()->GetSettingsEnum<FECsFX>(); }
		const FString& FLibrary::GetSettingsEnumPath_FX()				{ return NCsFXSettings::NCached::Str::FX; }
		FECsFX* FLibrary::GetDefault_ECsFX()							{ return &(Get()->Default_ECsFX); }

		#pragma endregion SkeletaMesh

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}