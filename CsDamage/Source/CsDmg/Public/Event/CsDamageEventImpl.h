// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Event/CsDamageEvent.h"
#include "Event/Copy/CsDamageEvent_Copy.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Types
#include "CsMacro_Cached.h"
#include "Value/CsAllocated_DamageValue.h"
#include "Range/CsAllocated_DamageRange.h"

class UObject;
struct FCsInterfaceMap;

// ValueType (NCsDamage::NValue::IValue)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// RangeType (NCsDamage::NRange::IRange)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// DataType (NCsDamage::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NEvent, NImpl, Impl)

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NImpl
		{
			using EventType = NCsDamage::NEvent::IEvent;
			using CopyType = NCsDamage::NEvent::NCopy::ICopy;

			/**
			* Basic implementation of the interface: EventType (NCsDamage::NEvent::IEvent)
			*/
			struct CSDMG_API FImpl final : public EventType,
										   public CopyType,
										   public ICsReset
			{
			public:

				static const FName Name;

			private:

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NEvent, NImpl, Impl);

				using ValueType = NCsDamage::NValue::IValue;
				using AllocatedValueType = NCsDamage::NValue::FAllocated;
				using RangeType = NCsDamage::NRange::IRange;
				using AllocatedRangeType = NCsDamage::NRange::FAllocated;
				using DataType = NCsDamage::NData::IData;

				FCsInterfaceMap InterfaceMap;

			public:

				// IEvent

				float Damage;

				AllocatedValueType DamageValue;

				AllocatedRangeType DamageRange;

				FECsDamageData Type;

				DataType* Data;

				UObject* Instigator;

				UObject* Causer;

				FVector DamageDirection;

				FECsHitType HitType;

				FHitResult Origin;

				FHitResult HitResult;

				TArray<UObject*> IgnoreObjects;

				uint32 ModifierMask;

			public:

				FImpl();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return const_cast<FCsInterfaceMap*>(&InterfaceMap); }

			#pragma endregion ICsGetInterfaceMap

			// IEvent
			#pragma region
			public:

				FORCEINLINE const float& GetDamage() const { return Damage; }
				FORCEINLINE const ValueType* GetDamageValue() const { return DamageValue.GetValue(); }
				FORCEINLINE const RangeType* GetDamageRange() const { return DamageRange.GetRange(); }
				FORCEINLINE const FECsDamageData& GetDataType() const { return Type; }
				FORCEINLINE DataType* GetData() const { return Data; }
				FORCEINLINE UObject* GetInstigator() const { return Instigator; }
				FORCEINLINE UObject* GetCauser() const { return Causer; }
				FORCEINLINE const FVector& GetDamageDirection() const { return DamageDirection; }
				FORCEINLINE const FECsHitType& GetHitType() const { return HitType; }
				FORCEINLINE const FHitResult& GetOrigin() const { return Origin; }
				FORCEINLINE const FHitResult& GetHitResult() const { return HitResult; }
				FORCEINLINE const TArray<UObject*>& GetIgnoreObjects() const { return IgnoreObjects; }
				FORCEINLINE const uint32& GetModifierMask() const { return ModifierMask; }

			#pragma endregion IEvent

			public:

				template<typename T>
				FORCEINLINE T* GetInstigator() const
				{
					return Cast<T>(GetInstigator());
				}

				template<typename T>
				FORCEINLINE T* GetCauser() const
				{
					return Cast<T>(GetCauser());
				}

			// CopyType (NCsDamage::NEvent::NCopy::ICopy)
			#pragma region
			public:

				/**
				* Copy all elements from another Event 
				*  EXCEPT:
				*   InterfaceMap: This needs to be unique per instance.
				*
				* @param From	Event to copy from.
				*/
				void Copy(const EventType* From);

			#pragma endregion CopyType (NCsDamage::NEvent::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				/**
				*
				*
				* @param Context	The calling context.
				* return			Whether the damage was successfully set.
				*/
				bool SetDamageChecked(const FString& Context);

			};
		}
	}
}