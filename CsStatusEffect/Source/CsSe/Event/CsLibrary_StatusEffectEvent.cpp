// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsLibrary_StatusEffectEvent.h"

// StatusEffect
#include "Event/CsStatusEffectEventImpl.h"
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

bool FCsLibrary_StatusEffectEvent::CopyChecked(const FString& Context, const ICsStatusEffectEvent* From, ICsStatusEffectEvent* To)
{
	// FCsStatusEffectEventImpl (ICsStatusEffectEvent)
	if (FCsStatusEffectEventImpl* ToImpl = SafePureStaticCastChecked<FCsStatusEffectEventImpl>(Context, To))
	{
		const FCsStatusEffectEventImpl* FromImpl = PureStaticCastChecked<FCsStatusEffectEventImpl>(Context, From);

		ToImpl->CopyFrom(FromImpl);
		return true;
	}
	// FCsStatusEffectEvent_DamageImpl (ICsStatusEffectEvent_Damage)
	if (FCsStatusEffectEvent_DamageImpl* ToImpl = SafePureStaticCastChecked<FCsStatusEffectEvent_DamageImpl>(Context, To))
	{
		const FCsStatusEffectEvent_DamageImpl* FromImpl = PureStaticCastChecked<FCsStatusEffectEvent_DamageImpl>(Context, From);

		ToImpl->CopyFrom(FromImpl);
		return true;
	}
	return false;
}