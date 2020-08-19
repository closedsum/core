// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"

bool FCsLibrary_DamageEvent::CopyChecked(const FString& Context, const ICsDamageEvent* From, ICsDamageEvent* To)
{
	// FCsDamageEventImpl (ICsDamageEvent)
	if (FCsDamageEventImpl* ToImpl = SafePureStaticCastChecked<FCsDamageEventImpl>(Context, To))
	{
		const FCsDamageEventImpl* FromImpl = PureStaticCastChecked<FCsDamageEventImpl>(Context, From);

		ToImpl->CopyFrom(FromImpl);
		return true;
	}
	return false;
}

bool FCsLibrary_DamageEvent::SetDamageChecked(const FString& Context, ICsDamageEvent* Event)
{
	// FCsDamageEventImpl (ICsDamageEvent)
	if (FCsDamageEventImpl* Impl = SafePureStaticCastChecked<FCsDamageEventImpl>(Context, Event))
	{
		return Impl->SetDamageChecked(Context);
	}
	return false;
}