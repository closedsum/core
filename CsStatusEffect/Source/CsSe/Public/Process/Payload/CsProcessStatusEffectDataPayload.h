// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StatusEffect.h"

class UObject;

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NProcess
		{
			struct CSSE_API FPayload
			{
			public:

			#define DataType NCsStatusEffect::NData::IData

			public:

				FECsStatusEffect Type;

				DataType* Data;

				UObject* Instigator;
				
				UObject* Causer;
				
				UObject* Receiver;

				FVector Direction;

				FHitResult HitResult;

				FPayload() :
					Type(),
					Data(nullptr),
					Instigator(nullptr),
					Causer(nullptr),
					Direction(0.0f),
					HitResult()
				{
				}

				FORCEINLINE void Reset()
				{
					Type = EMCsStatusEffect::Get().GetMAX();
					Data = nullptr;
					Instigator = nullptr;
					Causer = nullptr;
					Direction = FVector::ZeroVector;
					HitResult.Init();
				}

			#undef DataType
			};
		}
	}
}