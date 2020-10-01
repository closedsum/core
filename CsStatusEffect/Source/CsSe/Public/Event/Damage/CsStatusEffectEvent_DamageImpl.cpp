// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

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
				// IEvent
				Data(nullptr),
				Instigator(nullptr),
				Causer(nullptr),
				Receiver(nullptr),
				IgnoreObjects(),
				// IDamage
				DamageEvent()
			{
				InterfaceMap.SetRootName(FImpl::Name);

				InterfaceMap.Add<IEvent>(static_cast<IEvent*>(this));
				InterfaceMap.Add<IDamage>(static_cast<IDamage*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			void FImpl::CopyFrom(const FImpl* From)
			{
				// IEvent

				Data = From->Data;
				Instigator = From->Instigator;
				Causer = From->Causer;
				Receiver = From->Receiver;

				IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), From->IgnoreObjects.Max()));

				for (TWeakObjectPtr<UObject> O : From->IgnoreObjects)
				{
					IgnoreObjects.Add(O);
				}

				// IDamage

				DamageEvent.CopyFrom(&(From->DamageEvent));
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
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