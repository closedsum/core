// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Event/CsStatusEffectEvent.h"
#include "Types/CsGetStatusEffectEventType.h"
#include "Event/Damage/CsStatusEffectEvent_Damage.h"
#include "Event/Copy/CsStatusEffectEvent_Copy.h"
#include "Reset/CsReset.h"
// StatusEffect
#include "CsAllocated_StatusEffect.h"
// Damage
#include "Event/CsAllocated_DamageEvent.h"

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
		#define EventType NCsStatusEffect::NEvent::IEvent
		#define DamageSeEventType NCsStatusEffect::NEvent::NDamage::IDamage
		#define CopyType NCsStatusEffect::NEvent::NCopy::ICopy

			/**
			*/
			struct CSSE_API FImpl final : public EventType,
										  public ICsGetStatusEffectEventType,
										  public DamageSeEventType,
										  public CopyType,
										  public ICsReset
			{
			public:

				static const FName Name;

			#define StatusEffectType NCsStatusEffect::IStatusEffect
			#define AllocatedStatusEffectType NCsStatusEffect::FAllocated
			#define DataType NCsStatusEffect::NData::IData

			private:

				typedef NCsDamage::NEvent::FAllocated AllocatedDamageEventType;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// EventType (NCsStatusEffect::NEvent::IEvent)

				AllocatedStatusEffectType StatusEffect;

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

			// EventType (NCsStatusEffect::NEvent::IEvent)
			#pragma region
			public:

				FORCEINLINE StatusEffectType* GetStatusEffect() const { return StatusEffect.Get(); }
				FORCEINLINE DataType* GetData() const { return Data; }
				FORCEINLINE UObject* GetInstigator() const { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
				FORCEINLINE UObject* GetCauser() const { return Causer.IsValid() ? Causer.Get() : nullptr; }
				FORCEINLINE UObject* GetReceiver() const { return Receiver.IsValid() ? Receiver.Get() : nullptr; }
				FORCEINLINE const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const { return IgnoreObjects; }

			#pragma endregion EventType (NCsStatusEffect::NEvent::IEvent)

			// ICsGetStatusEffectEventType
			#pragma region
			public:

				FORCEINLINE const FECsStatusEffectEvent& GetStatusEffectEventType() const { return NCsStatusEffectEvent::Damage; }

			#pragma endregion ICsGetStatusEffectEventType

			// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)
			#pragma region
			public:

				FORCEINLINE NCsDamage::NEvent::IEvent* GetDamageEvent() const { return DamageEvent.Event; }

			#pragma endregion DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

			// CopyType (NCsStatusEffect::NEvent::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const EventType* From);

			#pragma endregion CopyType (NCsStatusEffect::NEvent::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				template<typename T>
				FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

				template<typename T>
				FORCEINLINE T* GetCauser() const { return Cast<T>(GetCauser()); }

			#undef StatusEffectType
			#undef AllocatedStatusEffectType
			#undef DataType
			};

		#undef EventType
		#undef DamageSeEventType
		#undef CopyType
		}
	}
}