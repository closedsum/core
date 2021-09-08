// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsBeamSettings.h"
#include "CsPrj.h"

#include "Managers/Beam/CsBeam.h"

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