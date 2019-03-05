// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Pool.h"

// PoolTransactionOrder
EMCsPoolTransactionOrder* EMCsPoolTransactionOrder::Instance;

EMCsPoolTransactionOrder& EMCsPoolTransactionOrder::Get()
{
	if (!Instance)
		Instance = new EMCsPoolTransactionOrder();
	return *Instance;
}

namespace ECsPoolTransactionOrder
{
	namespace Ref
	{
		CSCORE_API const Type FillAny = EMCsPoolTransactionOrder::Get().Add(Type::FillAny, TEXT("FillAny"), TEXT("Fill Any"));
		CSCORE_API const Type FillOrKill = EMCsPoolTransactionOrder::Get().Add(Type::FillOrKill, TEXT("FillOrKill"), TEXT("Fill or Kill"));
		CSCORE_API const Type ECsPoolTransactionOrder_MAX = EMCsPoolTransactionOrder::Get().Add(Type::ECsPoolTransactionOrder_MAX, TEXT("ECsPoolTransactionOrder_MAX"), TEXT("MAX"));
	}
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