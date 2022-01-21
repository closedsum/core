// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Event/CsStatusEffectEvent.h"
#include "Event/Damage/CsStatusEffectEvent_Damage.h"
#include "Reset/CsReset.h"
// Types
#include "Managers/Damage/Event/CsAllocated_DamageEvent.h"

class UObject;
struct FCsInterfaceMap;

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
		#define StatusEffectEventType NCsStatusEffect::NEvent::IEvent
		#define DamageSeEventType NCsStatusEffect::NEvent::NDamage::IDamage
		
			/**
			*/
			struct CSSE_API FImpl final : public StatusEffectEventType,
										  public DamageSeEventType,
										  public ICsReset
			{
			public:

				static const FName Name;

			#define StatusEffectType NCsStatusEffect::IStatusEffect
			#define DataType NCsStatusEffect::NData::IData

			private:

				typedef NCsDamage::NEvent::FAllocated AllocatedDamageEventType;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// StatusEffectEventType (NCsStatusEffect::NEvent::IEvent)

				StatusEffectType* StatusEffect;

				DataType* Data;

				TWeakObjectPtr<UObject> Instigator;

				TWeakObjectPtr<UObject> Causer;

				TWeakObjectPtr<UObject> Receiver;

				TArray<TWeakObjectPtr<UObject>> IgnoreObjects;

				// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

				AllocatedDamageEventType DamageEvent;

			public:

				FImpl();
				~FImpl();
	
				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// StatusEffectEventType (NCsStatusEffect::NEvent::IEvent)
			#pragma region
			public:

				FORCEINLINE StatusEffectType* GetStatusEffect() const { return StatusEffect; }
				FORCEINLINE DataType* GetData() const { return Data; }
				FORCEINLINE UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
				FORCEINLINE UObject* GetCauser() const { return Causer.IsValid() ? Causer.Get() : nullptr; }
				FORCEINLINE UObject* GetReceiver() const { return Receiver.IsValid() ? Receiver.Get() : nullptr; }
				FORCEINLINE const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const { return IgnoreObjects; }

			#pragma endregion StatusEffectEventType (NCsStatusEffect::NEvent::IEvent)

			// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)
			#pragma region
			public:

				FORCEINLINE NCsDamage::NEvent::IEvent* GetDamageEvent() const { return DamageEvent.Event; }

			#pragma endregion DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

			public:

				template<typename T>
				FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

				template<typename T>
				FORCEINLINE T* GetCauser() const { return Cast<T>(GetCauser()); }

				/**
				* Copy all elements from another Event 
				*  EXCEPT:
				*   InterfaceMap: This needs to be unique per instance.
				*
				* @param From	Event to copy from.
				*/
				void CopyFrom(const FImpl* From);

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			#undef StatusEffectType
			#undef DataType
			};

		#undef StatusEffectEventType
		#undef DamageSeEventType
		}
	}
}