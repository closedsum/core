// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/Enum/CsEnumMask_int32.h"
#include "Types/Enum/CsEnumStructMaskMap.h"

#include "CsTypes_Team.generated.h"
#pragma once

// Team
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsTeam : public FECsEnumMask_int32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_MASK_INT32_BODY(FECsTeam)
};

CS_DEFINE_ENUM_MASK_INT32_GET_TYPE_HASH(FECsTeam)

struct CSCORE_API EMCsTeam : public TCsEnumStructMaskMap<FECsTeam, int32>
{
	CS_ENUM_STRUCT_MASK_MAP_BODY(EMCsTeam, FECsTeam, int32)
};

namespace NCsTeam
{
	typedef FECsTeam Type;
	typedef EMCsTeam EnumMapType;
}

#pragma endregion Team