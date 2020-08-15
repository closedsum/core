// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"

void FCsLibrary_DamageEvent::CopyChecked(const FString& Context, ICsDamageEvent* From, ICsDamageEvent* To)
{
	// FCsDamageEventImpl (ICsDamageEvent)
	if (FCsDamageEventImpl* ToImpl = SafePureStaticCastChecked<FCsDamageEventImpl>(Context, To))
	{
		FCsDamageEventImpl* FromImpl = PureStaticCastChecked<FCsDamageEventImpl>(Context, From);

		ToImpl->CopyFrom(FromImpl);
	}
	else
	{
		checkf(0, TEXT("%s: Failed to copy From to To."), *Context);
	}
}

void FCsLibrary_DamageEvent::SetDamageChecked(const FString& Context, ICsDamageEvent* Event)
{
	// FCsDamageEventImpl (ICsDamageEvent)
	if (FCsDamageEventImpl* Impl = SafePureStaticCastChecked<FCsDamageEventImpl>(Context, Event))
	{
		Impl->SetDamageChecked(Context);
	}
	else
	{
		checkf(0, TEXT("%s: Failed to set damage for Event"), *Context);
	}
}