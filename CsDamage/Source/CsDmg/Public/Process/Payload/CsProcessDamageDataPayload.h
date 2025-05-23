// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

class UObject;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsDamage
{
	namespace NData
	{
		namespace NProcess
		{
			struct CSDMG_API FPayload
			{
			private:

				using ValueType = NCsDamage::NValue::IValue;
				using RangeType = NCsDamage::NRange::IRange;
				using ModifierType = NCsDamage::NModifier::IModifier;
				using DataType = NCsDamage::NData::IData;

			public:

				ValueType* Value;
			
			private:

				bool bRange;

				RangeType* Range;
			
			public:

				FECsDamageData Type;

				DataType* Data;

				UObject* Instigator;
				
				UObject* Causer;
				
				FVector Direction;

				FHitResult HitResult;
				
				TArray<ModifierType*> Modifiers;

				FPayload() :
					Value(nullptr),
					Range(nullptr),
					Type(),
					Data(nullptr),
					Instigator(nullptr),
					Causer(nullptr),
					Direction(0.0f),
					HitResult(),
					Modifiers()
				{
				}

				void SetTypeChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& InType);

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
					Type = EMCsDamageData::Get().GetMAX();
					Data = nullptr;
					Instigator = nullptr;
					Causer = nullptr;
					Direction = FVector::ZeroVector;
					HitResult.Init();
					Modifiers.Reset(Modifiers.Max());
				}
			};
		}
	}
}