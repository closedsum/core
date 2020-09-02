// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"

// PoolTransaction
#pragma region

namespace NCsPoolTransaction
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolTransaction, Allocate);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolTransaction, Spawn);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransaction, PreDeallocate, "Pre-Deallocate");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolTransaction, Deallocate);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransaction, DeallocateByQueue, "Deallocate by Queue");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransaction, DeallocateByUnknown, "Deallocate by Unknown");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransaction, DeallocateByLifeTime, "Deallocate by LifeTime");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolTransaction, Destroy);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransaction, ECsPoolTransaction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPoolTransaction_MAX;

	namespace Str
	{
		CSCORE_API const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		CSCORE_API const TCsString PreDeallocate = TCsString(TEXT("PreDeallocate"), TEXT("predeallocate"), TEXT("PreDeallocating"));
		CSCORE_API const TCsString Deallocate = TCsString(TEXT("Deallocate"), TEXT("deallocate"), TEXT("Deallocating"));
	}
}

#pragma endregion PoolTransaction

// PoolTransactionOrder
#pragma region

namespace NCsPoolTransactionOrder
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransactionOrder, FillAny, "Fill Any");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransactionOrder, FillOrKill, "Fill or Kill");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolTransactionOrder, ECsPoolTransactionOrder_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPoolTransactionOrder_MAX;
}

#pragma endregion PoolTransactionOrder

// PoolObjectState
#pragma region

namespace NCsPooledObjectState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolObjectState, WarmUp, "Warm Up");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolObjectState, Active);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPoolObjectState, Inactive);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPoolObjectState, ECsPooledObjectState_MAX, "MAX");
	}
}

#pragma endregion PoolObjectState

// PooledObjectConstruction
#pragma region

namespace NCsPooledObjectConstruction
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectConstruction, Object);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectConstruction, Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPooledObjectConstruction, ECsPooledObjectConstruction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPooledObjectConstruction_MAX;
}

#pragma endregion PooledObjectConstruction

// PooledObjectUpdate
#pragma region

namespace NCsPooledObjectUpdate
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectUpdate, Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectUpdate, Manager);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectUpdate, Owner);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPooledObjectUpdate, Instigator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPooledObjectUpdate, ECsPooledObjectUpdate_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPooledObjectUpdate_MAX;
}

#pragma endregion PooledObjectConstruction

// ManagerPooledObject
#pragma region

namespace NCsManagerPooledObject
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsManagerPooledObject, Dynamic);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsManagerPooledObject, Fixed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsManagerPooledObject, ECsManagerPooledObject_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsManagerPooledObject_MAX;
}

#pragma endregion ManagerPooledObject