// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Update.generated.h"

// UpdateGroup
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FECsUpdateGroup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUpdateGroup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUpdateGroup)

struct CSTYPES_API EMCsUpdateGroup final : public TCsEnumStructMap<FECsUpdateGroup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUpdateGroup, FECsUpdateGroup, uint8)
};

namespace NCsUpdateGroup
{
	typedef FECsUpdateGroup Type;
	typedef EMCsUpdateGroup EnumMapType;

	extern CSTYPES_API const Type Custom;
	extern CSTYPES_API const Type EditorEngine;
	extern CSTYPES_API const Type GameInstance;
	extern CSTYPES_API const Type GameState;
	extern CSTYPES_API const Type Menu;
}

#pragma endregion UpdateGroup