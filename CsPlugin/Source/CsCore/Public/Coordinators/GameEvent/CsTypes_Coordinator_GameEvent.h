// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Coordinator_GameEvent.generated.h"

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

	/** Broadcast GameEvents Immediately */
	extern CSCORE_API const Type None;
	/** Broadcast GameEvents during GameInstance->Tick() */
	extern CSCORE_API const Type GameInstance;
	/** Broadcast GameEvents during GameState->Update() */
	extern CSCORE_API const Type GameState;
	/** Broadcast GameEvents during ControllerId 0's ManagerInput->PostProcessInput. */
	extern CSCORE_API const Type ManagerInput0;
	/** Broadcast GameEvents during ControllerId 1's ManagerInput->PostProcessInput. */
	extern CSCORE_API const Type ManagerInput1;

	FORCEINLINE static bool IsManagerInput(const Type& Group)
	{
		return Group == ManagerInput0 || ManagerInput1;
	}

	FORCEINLINE static int32 GetManagerInputIndex(const Type& Group)
	{
		check(IsManagerInput(Group));

		return Group == ManagerInput0 ? 0 : 1;
	}
}

#pragma endregion GameEventCoordinatorGroup