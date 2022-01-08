// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_WeaponModifier.generated.h"

// WeaponModifier
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponModifier)

struct CSWP_API EMCsWeaponModifier : public TCsEnumStructMap<FECsWeaponModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponModifier, FECsWeaponModifier, uint8)
};

namespace NCsWeaponModifier
{
	typedef FECsWeaponModifier Type;
	typedef EMCsWeaponModifier EnumMapType;

	extern CSWP_API const Type PrjWp_TimeBetweenShots;
}

#pragma endregion WeaponModifier