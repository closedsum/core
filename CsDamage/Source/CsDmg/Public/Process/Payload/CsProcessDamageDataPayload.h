// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"

class UObject;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsDamage
{
	namespace NData
	{
		namespace NProcess
		{
			struct CSDMG_API FPayload
			{
			public:

			#define ValueType NCsDamage::NValue::IValue
			#define RangeType NCsDamage::NRange::IRange
			#define ModifierResourceType NCsDamage::NModifier::FResource
			#define DataType NCsDamage::NData::IData

				ValueType* Value;
			
			private:

				bool bRange;

				RangeType* Range;
			
			public:

				DataType* Data;

				UObject* Instigator;
				
				UObject* Causer;
				
				FVector Direction;

				FHitResult HitResult;
				
				TArray<ModifierResourceType*> Modifiers;

				FPayload() :
					Value(nullptr),
					Range(nullptr),
					Data(nullptr),
					Instigator(nullptr),
					Causer(nullptr),
					Direction(0.0f),
					HitResult(),
					Modifiers()
				{
				}

				FORCEINLINE void SetRange(RangeType* InRange)
				{
					bRange = true;
					Range  = InRange;
				}
				FORCEINLINE RangeType* GetRange() const { return Range; }
				FORCEINLINE bool HasSetRange() const { return bRange; }

				FORCEINLINE void Reset()
				{
					Value = nullptr;
					bRange = false;
					Range = nullptr;
					Data = nullptr;
					Instigator = nullptr;
					Causer = nullptr;
					Direction = FVector::ZeroVector;
					HitResult.Init();
					Modifiers.Reset(Modifiers.Max());
				}

			#undef ValueType
			#undef RangeType
			#undef ModifierResourceType
			#undef DataType
			};
		}
	}
}