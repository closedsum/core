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