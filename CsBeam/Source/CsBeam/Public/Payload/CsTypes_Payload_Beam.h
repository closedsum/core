// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Payload_Beam.generated.h"

// BeamPayload
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FECsBeamPayload : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBeamPayload)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBeamPayload)

struct CSBEAM_API EMCsBeamPayload : public TCsEnumStructMap<FECsBeamPayload, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsBeamPayload, FECsBeamPayload, uint8)
};

namespace NCsBeamPayload
{
	typedef FECsBeamPayload Type;
	typedef EMCsBeamPayload EnumMapType;

	extern CSBEAM_API const Type Beam;
	extern CSBEAM_API const Type BeamDamageModifier;
}

#pragma endregion BeamPayload