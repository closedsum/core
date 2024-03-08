// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Payload/CsTypes_Payload_Beam.h"
#include "CsBeam.h"

// NCsBeamPayload
#pragma region

namespace NCsBeamPayload
{
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(Beam, "NCsBeam::NPayload::IPayload");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(BeamDamageModifier, "ICsPayload_BeamDamageModifier");
}

#pragma endregion NCsBeamPayload