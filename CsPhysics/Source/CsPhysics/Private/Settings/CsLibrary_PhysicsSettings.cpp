
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_PhysicsSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsPhysicsSettings.h"

namespace NCsPhysics
{
	namespace NSettings
	{
		UCsPhysicsSettings* FLibrary::Get() { return GetMutableDefault<UCsPhysicsSettings>(); }

		#define USING_NS_CACHED using namespace NCsPhysics::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsPhysics::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}