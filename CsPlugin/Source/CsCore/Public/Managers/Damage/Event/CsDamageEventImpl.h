// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Interfaces
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/Damage/Value/CsAllocated_DamageValue.h"
#include "Managers/Damage/Range/CsAllocated_DamageRange.h"
#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

class ICsData_Damage;

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		* Basic implementation of the interface: NCsDamage::NEvent::IEvent
		*/
		struct CSCORE_API FImpl final : public IEvent,
										public ICsReset
		{
		public:

			static const FName Name;

		private:

			typedef NCsDamage::NValue::IValue ValueType;
			typedef NCsDamage::NValue::FAllocated AllocatedValueType;
			typedef NCsDamage::NRange::IRange RangeType;
			typedef NCsDamage::NRange::FAllocated AllocatedRangeType;

			FCsInterfaceMap InterfaceMap;

		public:

			// IEvent

			float Damage;

			AllocatedValueType DamageValue;

			AllocatedRangeType DamageRange;

			ICsData_Damage* Data;

			UObject* Instigator;

			UObject* Causer;

			FECsHitType HitType;

			FHitResult Origin;

			FHitResult HitResult;

			TArray<UObject*> IgnoreObjects;

		public:

			FImpl();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return const_cast<FCsInterfaceMap*>(&InterfaceMap);
			}

		#pragma endregion ICsGetInterfaceMap

		// IEvent
		#pragma region
		public:

			FORCEINLINE const float& GetDamage() const
			{
				return Damage;
			}

			FORCEINLINE const ValueType* GetDamageValue() const
			{
				return DamageValue.Value;
			}

			FORCEINLINE const RangeType* GetDamageRange() const
			{
				return DamageRange.Range;
			}

			FORCEINLINE ICsData_Damage* GetData() const
			{
				return Data;
			}

			FORCEINLINE UObject* GetInstigator() const
			{
				return Instigator;
			}

			FORCEINLINE UObject* GetCauser() const
			{
				return Causer;
			}

			FORCEINLINE const FECsHitType& GetHitType() const
			{
				return HitType;
			}

			FORCEINLINE const FHitResult& GetOrigin() const
			{
				return Origin;
			}

			FORCEINLINE const FHitResult& GetHitResult() const
			{
				return HitResult;
			}

			FORCEINLINE const TArray<UObject*>& GetIgnoreObjects() const
			{
				return IgnoreObjects;
			}

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

			/**
			* Copy all elements from another Event 
			*  EXCEPT:
			*   InterfaceMap: This needs to be unique per instance.
			*
			* @param From	Event to copy from.
			*/
			void CopyFrom(const FImpl* From);

			/**
			*
			*
			* @param Context	The calling context.
			* return			Whether the damage was successfully set.
			*/
			bool SetDamageChecked(const FString& Context);

		// ICsReset
		#pragma region

			void Reset();

		#pragma endregion ICsReset
		};
	}
}