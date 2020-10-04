// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"

#define EventType NCsDamage::NEvent::IEvent
bool FCsLibrary_DamageEvent::CopyChecked(const FString& Context, const EventType* From, EventType* To)
{
#undef EventType
	// NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
	{
		typedef NCsDamage::NEvent::FImpl ImplType;

		if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
		{
			const ImplType* FromImpl = PureStaticCastChecked<ImplType>(Context, From);

			ToImpl->CopyFrom(FromImpl);
			return true;
		}
	}
	return false;
}

#define EventType NCsDamage::NEvent::IEvent
bool FCsLibrary_DamageEvent::SetDamageChecked(const FString& Context, EventType* Event)
{
#undef EventType
	// NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
	{
		typedef NCsDamage::NEvent::FImpl ImplType;

		if (ImplType* Impl = SafePureStaticCastChecked<ImplType>(Context, Event))
		{
			return Impl->SetDamageChecked(Context);
		}
	}
	return false;
}