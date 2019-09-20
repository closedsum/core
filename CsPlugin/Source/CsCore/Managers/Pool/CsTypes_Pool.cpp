// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"

// PoolTransaction
#pragma region

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

#pragma endregion PoolTransaction

// PoolTransactionOrder
#pragma region

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

#pragma endregion PoolTransactionOrder

// PoolObjectState
#pragma region

namespace NCsPooledObjectState
{
	namespace Ref
	{
		CSCORE_API const Type WarmUp = EMCsPoolObjectState::Get().Add(Type::WarmUp, TEXT("WarmUp"), TEXT("Warm Up"));
		CSCORE_API const Type Active = EMCsPoolObjectState::Get().Add(Type::Active, TEXT("Active"));
		CSCORE_API const Type Inactive = EMCsPoolObjectState::Get().Add(Type::Inactive, TEXT("Inactive"));
		CSCORE_API const Type ECsPooledObjectState_MAX = EMCsPoolObjectState::Get().Add(Type::ECsPooledObjectState_MAX, TEXT("ECsPooledObjectState_MAX"), TEXT("MAX"));
	}
}

#pragma endregion PoolObjectState