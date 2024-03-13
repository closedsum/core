// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMask_int32.h"
#include "Types/Enum/CsEnumStructMaskMap.h"

#include "CsTypes_Team.generated.h"

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