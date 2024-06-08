// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Pool/CsTypes_Pool.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Pool)

// PoolTransaction
#pragma region

namespace NCsPoolTransaction
{
	namespace Ref
	{
		typedef EMCsPoolTransaction EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Allocate);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Spawn);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PreDeallocate, "Pre-Deallocate");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Deallocate);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(DeallocateByQueue, "Deallocate by Queue");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(DeallocateByUnknown, "Deallocate by Unknown");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(DeallocateByLifeTime, "Deallocate by LifeTime");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Destroy);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPoolTransaction_MAX, "MAX");
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
		typedef EMCsPoolTransactionOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FillAny, "Fill Any");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FillOrKill, "Fill or Kill");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPoolTransactionOrder_MAX, "MAX");
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
		typedef EMCsPooledObjectState EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(WarmUp, "Warm Up");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Active);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Inactive);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPooledObjectState_MAX, "MAX");
	}
}

namespace NCsPooledObject
{
	namespace NState
	{
		namespace Ref
		{
			typedef EMState EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(WarmUp, "Warm Up");
			CSCORE_API CS_ADD_TO_ENUM_MAP(Active);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Inactive);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EState_MAX, "MAX");
		}
	}
}

#pragma endregion PoolObjectState

// PooledObjectConstruction
#pragma region

namespace NCsPooledObjectConstruction
{
	namespace Ref
	{
		typedef EMCsPooledObjectConstruction EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Object);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CustomObject, "Custom Object");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPooledObjectConstruction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPooledObjectConstruction_MAX;
}

namespace NCsPooledObject
{
	namespace NConstruction
	{
		namespace Ref
		{
			typedef EMConstruction EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Object);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CustomObject, "Custom Object");
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EConstruction_MAX, "MAX");
		}
	}
}

#pragma endregion PooledObjectConstruction

// PooledObjectUpdate
#pragma region

namespace NCsPooledObjectUpdate
{
	namespace Ref
	{
		typedef EMCsPooledObjectUpdate EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Manager);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Owner);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Instigator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPooledObjectUpdate_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPooledObjectUpdate_MAX;
}

namespace NCsPooledObject
{
	namespace NUpdate
	{
		namespace Ref
		{
			typedef EMUpdate EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(None);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Manager);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Owner);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Instigator);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EUpdate_MAX, "MAX");
		}
	}
}

#pragma endregion PooledObjectConstruction

// ManagerPooledObject
#pragma region

namespace NCsManagerPooledObject
{
	namespace Ref
	{
		typedef EMCsManagerPooledObject EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Dynamic);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Fixed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsManagerPooledObject_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsManagerPooledObject_MAX;
}

#pragma endregion ManagerPooledObject