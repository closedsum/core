// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Coordinator_GameEvent.generated.h"
#pragma once

// GameEventCoordinatorGroup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameEventCoordinatorGroup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameEventCoordinatorGroup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameEventCoordinatorGroup)

struct CSCORE_API EMCsGameEventCoordinatorGroup : public TCsEnumStructMap<FECsGameEventCoordinatorGroup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup, uint8)
};

namespace NCsGameEventCoordinatorGroup
{
	typedef FECsGameEventCoordinatorGroup Type;
	typedef EMCsGameEventCoordinatorGroup EnumMapType;

	extern CSCORE_API const Type GameInstance;
	extern CSCORE_API const Type GameState;
	extern CSCORE_API const Type InputManager0;
	extern CSCORE_API const Type InputManager1;
}

#pragma endregion GameEventCoordinatorGroup