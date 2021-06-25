// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Interaction.generated.h"
#pragma once

// Menu
#pragma region

/**
* Enum for Menu types.
*/
USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FECsInteraction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInteraction)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsInteraction)

struct CSINTERACTIVE_API EMCsInteraction final : public TCsEnumStructMap<FECsInteraction, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsInteraction, FECsInteraction, uint8)
};

namespace NCsInteraction
{
	typedef FECsInteraction Type;
	typedef EMCsInteraction EnumMapType;
}

#pragma endregion Menu