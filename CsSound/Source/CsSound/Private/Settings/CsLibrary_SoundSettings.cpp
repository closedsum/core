
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_SoundSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsSoundSettings.h"
// Interface
#include "SourceControl/Tool/CsGetSourceControlTool.h"

namespace NCsSound
{
	namespace NSettings
	{
		UCsSoundSettings* FLibrary::Get() { return GetMutableDefault<UCsSoundSettings>(); }

		#define USING_NS_CACHED using namespace NCsSound::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsSound::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// Sound
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_Sound()	{ return Get()->GetSettingsEnum<FECsSound>(); }
		const FString& FLibrary::GetSettingsEnumPath_Sound()				{ return NCsSoundSettings::NCached::Str::Sound; }
		FECsSound* FLibrary::GetDefault_ECsSound()							{ return &(Get()->Default_ECsSound); }

		#pragma endregion SkeletaMesh

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}