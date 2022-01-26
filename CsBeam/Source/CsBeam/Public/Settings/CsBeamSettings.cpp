// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsBeamSettings.h"
#include "CsBeam.h"

#include "Managers/Beam/ICsBeam.h"

// Cached
#pragma region

namespace NCsBeamSettings
{
	namespace Str
	{
		CSBEAM_API CS_DEFINE_CACHED_STRING(Beam, "UCsBeamSettings.ECsBeam");
		CSBEAM_API CS_DEFINE_CACHED_STRING(BeamClass, "UCsBeamSettings.ECsBeamClass");
	}
}

#pragma endregion Cached

UCsBeamSettings::UCsBeamSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}