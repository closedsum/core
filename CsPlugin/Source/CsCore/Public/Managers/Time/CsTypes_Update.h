// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Update.generated.h"
#pragma once

// UpdateGroup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsUpdateGroup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUpdateGroup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUpdateGroup)

struct CSCORE_API EMCsUpdateGroup final : public TCsEnumStructMap<FECsUpdateGroup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUpdateGroup, FECsUpdateGroup, uint8)
};

namespace NCsUpdateGroup
{
	typedef FECsUpdateGroup Type;
	typedef EMCsUpdateGroup EnumMapType;

	extern CSCORE_API const Type EditorEngine;
	extern CSCORE_API const Type GameInstance;
	extern CSCORE_API const Type GameState;
	extern CSCORE_API const Type Menu;
}

#pragma endregion UpdateGroup