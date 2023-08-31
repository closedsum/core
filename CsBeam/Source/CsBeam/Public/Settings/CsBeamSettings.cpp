// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsBeamSettings.h"
#include "CsBeam.h"

#include "Managers/Beam/ICsBeam.h"

// Cached
#pragma region

namespace NCsBeamSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSBEAM_API CS_DEFINE_CACHED_STRING(Beam, "UCsBeamSettings.ECsBeam");
			CSBEAM_API CS_DEFINE_CACHED_STRING(BeamClass, "UCsBeamSettings.ECsBeamClass");
		}
	}
}

#pragma endregion Cached

UCsBeamSettings::UCsBeamSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}