// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Range/CsDamageRangeImpl.h"

bool FCsLibrary_DamageRange::CopyChecked(const FString& Context, const ICsDamageRange* From, ICsDamageRange* To)
{
	// FCsDamageValuePointImpl (ICsDamageRange)
	if (FCsDamageRangeImpl* ToImpl = SafePureStaticCastChecked<FCsDamageRangeImpl>(Context, To))
	{
		ToImpl->MinRange = From->GetMinRange();
		ToImpl->MaxRange = From->GetMaxRange();
		return true;
	}
	return false;
}