// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsStatusEffect::NEvent::NDamage::FImpl::Name = FName("NCsStatusEffect::NEvent::NDamage::FImpl");;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(),
				// StatusEffectEventType (NCsStatusEffect::NEvent::IEvent)
				StatusEffect(nullptr),
				Data(nullptr),
				Instigator(nullptr),
				Causer(nullptr),
				Receiver(nullptr),
				IgnoreObjects(),
				// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)
				DamageEvent()
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				typedef NCsStatusEffect::NEvent::IEvent StatusEffectEventType;
				typedef NCsStatusEffect::NEvent::NDamage::IDamage DamageSeEventType;
		
				InterfaceMap->Add<StatusEffectEventType>(static_cast<StatusEffectEventType*>(this));
				InterfaceMap->Add<DamageSeEventType>(static_cast<DamageSeEventType*>(this));
				InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			void FImpl::CopyFrom(const FImpl* From)
			{
				// StatusEffectEventType(NCsStatusEffect::NEvent::IEvent)

				Data = From->Data;
				Instigator = From->Instigator;
				Causer = From->Causer;
				Receiver = From->Receiver;

				IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), From->IgnoreObjects.Max()));

				for (TWeakObjectPtr<UObject> O : From->IgnoreObjects)
				{
					IgnoreObjects.Add(O);
				}

				// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

				DamageEvent.CopyFrom(&(From->DamageEvent));
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				StatusEffect = nullptr;
				Data = nullptr;
				Instigator = nullptr;
				Causer = nullptr;
				Receiver = nullptr;
				IgnoreObjects.Reset(IgnoreObjects.Max());
				DamageEvent.Reset();
			}

			#pragma endregion ICsReset
		}
	}
}