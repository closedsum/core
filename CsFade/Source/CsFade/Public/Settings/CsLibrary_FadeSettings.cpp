// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_FadeSettings.h"
#include "CsFade.h"

// Settings
#include "Settings/CsFadeSettings.h"

namespace NCsFade
{
	namespace NSettings
	{
		UCsFadeSettings* FLibrary::Get() { return GetMutableDefault<UCsFadeSettings>(); }
	}
}