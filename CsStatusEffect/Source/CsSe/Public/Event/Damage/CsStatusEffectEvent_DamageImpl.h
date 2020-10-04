// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Event/Damage/CsStatusEffectEvent_Damage.h"
#include "Reset/CsReset.h"
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/Damage/Event/CsAllocated_DamageEvent.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsData_StatusEffect;

namespace NCsDamage {
	namespace NEvent {
		struct IEvent; } }

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
			/**
			*/
			struct CSSE_API FImpl final : public IEvent,
										  public IDamage,
										  public ICsReset
			{
			public:

				static const FName Name;

			private:

				typedef NCsDamage::NEvent::FAllocated AllocatedDamageEventType;

				// ICsGetInterfaceMap

				FCsInterfaceMap InterfaceMap;

			public:

				// IEvent

				ICsData_StatusEffect* Data;

				TWeakObjectPtr<UObject> Instigator;

				TWeakObjectPtr<UObject> Causer;

				TWeakObjectPtr<UObject> Receiver;

				TArray<TWeakObjectPtr<UObject>> IgnoreObjects;

				// IDamage

				AllocatedDamageEventType DamageEvent;

			public:

				FImpl();

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

				FORCEINLINE ICsData_StatusEffect* GetData() const
				{
					return Data;
				}

				FORCEINLINE UObject* GetInstigator() const
				{
					return Instigator.IsValid() ? Instigator.Get() : nullptr;
				}

				FORCEINLINE UObject* GetCauser() const
				{
					return Causer.IsValid() ? Causer.Get() : nullptr;
				}

				FORCEINLINE UObject* GetReceiver() const
				{
					return Receiver.IsValid() ? Receiver.Get() : nullptr;
				}

				FORCEINLINE const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const
				{
					return IgnoreObjects;
				}

			#pragma endregion IEvent

			// IDamage
			#pragma region
			public:

				FORCEINLINE NCsDamage::NEvent::IEvent* GetDamageEvent() const
				{
					return DamageEvent.Event;
				}

			#pragma endregion IDamage

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

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset
			};
		}
	}
}