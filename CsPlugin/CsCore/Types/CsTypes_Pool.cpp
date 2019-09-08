// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Pool.h"

// PoolTransaction
CS_DEFINE_ENUM_MAP_BODY(EMCsPoolTransaction)

namespace NCsPoolTransaction
{
	namespace Ref
	{
		CSCORE_API const Type Allocate = EMCsPoolTransaction::Get().Add(Type::Allocate, TEXT("Allocate"));
		CSCORE_API const Type PreDeallocate = EMCsPoolTransaction::Get().Add(Type::PreDeallocate, TEXT("PreDeallocate"));
		CSCORE_API const Type Deallocate = EMCsPoolTransaction::Get().Add(Type::Deallocate, TEXT("Deallocate"));
		CSCORE_API const Type ECsPoolTransaction_MAX = EMCsPoolTransaction::Get().Add(Type::ECsPoolTransaction_MAX, TEXT("ECsPoolTransaction_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPoolTransaction_MAX;

	namespace Str
	{
		CSCORE_API const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		CSCORE_API const TCsString PreDeallocate = TCsString(TEXT("PreDeallocate"), TEXT("predeallocate"), TEXT("PreDeallocating"));
		CSCORE_API const TCsString Deallocate = TCsString(TEXT("Deallocate"), TEXT("deallocate"), TEXT("Deallocating"));
	}
}

// PoolTransactionOrder
CS_DEFINE_ENUM_MAP_BODY(EMCsPoolTransactionOrder)

namespace NCsPoolTransactionOrder
{
	namespace Ref
	{
		CSCORE_API const Type FillAny = EMCsPoolTransactionOrder::Get().Add(Type::FillAny, TEXT("FillAny"), TEXT("Fill Any"));
		CSCORE_API const Type FillOrKill = EMCsPoolTransactionOrder::Get().Add(Type::FillOrKill, TEXT("FillOrKill"), TEXT("Fill or Kill"));
		CSCORE_API const Type ECsPoolTransactionOrder_MAX = EMCsPoolTransactionOrder::Get().Add(Type::ECsPoolTransactionOrder_MAX, TEXT("ECsPoolTransactionOrder_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPoolTransactionOrder_MAX;
}

// PoolObjectState
EMCsPoolObjectState* EMCsPoolObjectState::Instance;

EMCsPoolObjectState& EMCsPoolObjectState::Get()
{
	if (!Instance)
		Instance = new EMCsPoolObjectState();
	return *Instance;
}

namespace ECsPooledObjectState
{
	namespace Ref
	{
		CSCORE_API const Type WarmUp = EMCsPoolObjectState::Get().Add(Type::WarmUp, TEXT("WarmUp"), TEXT("Warm Up"));
		CSCORE_API const Type Active = EMCsPoolObjectState::Get().Add(Type::Active, TEXT("Active"));
		CSCORE_API const Type Inactive = EMCsPoolObjectState::Get().Add(Type::Inactive, TEXT("Inactive"));
		CSCORE_API const Type ECsPooledObjectState_MAX = EMCsPoolObjectState::Get().Add(Type::ECsPooledObjectState_MAX, TEXT("ECsPooledObjectState_MAX"), TEXT("MAX"));
	}
}