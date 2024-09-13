// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StatusEffect.h"

class UObject;

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

// NCsModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsModifier, IModifier)

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
			#define CsModifierType NCsModifier::IModifier

			public:

				FECsStatusEffect Type;

				FECsStatusEffectImpl ImplType;

				DataType* Data;

				UObject* Instigator;
				
				UObject* Causer;
				
				UObject* Receiver;

				FVector3f Direction;

				FHitResult HitResult;

				TArray<CsModifierType*> Modifiers;

				FPayload() :
					Type(),
					ImplType(),
					Data(nullptr),
					Instigator(nullptr),
					Causer(nullptr),
					Direction(0.0f),
					HitResult(),
					Modifiers()
				{
				}

				FORCEINLINE void Reset()
				{
					Type = EMCsStatusEffect::Get().GetMAX();
					ImplType = EMCsStatusEffectImpl::Get().GetMAX();
					Data = nullptr;
					Instigator = nullptr;
					Causer = nullptr;
					Direction = FVector3f::ZeroVector;
					HitResult.Init();
					Modifiers.Reset(Modifiers.Max());
				}

			#undef DataType
			#undef CsModifierType
			};
		}
	}
}