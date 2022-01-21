// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsLibrary_StatusEffectEvent.h"

// StatusEffect
#include "Event/CsStatusEffectEventImpl.h"
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

namespace NCsStatusEffect
{
	namespace NEvent
	{
		#define EventType NCsStatusEffect::NEvent::IEvent
		bool FLibrary::CopyChecked(const FString& Context, const EventType* From, EventType* To)
		{
		#undef EventType
			/*
			// NCsStatusEffect::NEvent::FImpl (NCsStatusEffect::NEvent::IEvent)
			{
				typedef NCsStatusEffect::NEvent::FImpl ImplType;

				if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
				{
					const ImplType* FromImpl = PureStaticCastChecked<ImplType>(Context, From);

					ToImpl->CopyFrom(FromImpl);
					return true;
				}
			}
			// NCsStatusEffect::NEvent::NDamage::FImpl (NCsStatusEffect::NEvent::NDamage::IDamage)
			{
				typedef NCsStatusEffect::NEvent::NDamage::FImpl ImplType;

				if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
				{
					const ImplType* FromImpl = PureStaticCastChecked<ImplType>(Context, From);

					ToImpl->CopyFrom(FromImpl);
					return true;
				}
			}
			*/
			return false;
		}
	}
}