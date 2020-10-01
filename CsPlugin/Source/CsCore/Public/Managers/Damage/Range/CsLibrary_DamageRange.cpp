// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Range/CsDamageRangeImpl.h"

bool FCsLibrary_DamageRange::CopyChecked(const FString& Context, const NCsDamage::NRange::IRange* From, NCsDamage::NRange::IRange* To)
{
	// NCsDamage::NRange::FImpl (NCsDamage::NRange::IRange)
	{
		typedef NCsDamage::NRange::FImpl ImplType;

		if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
		{
			ToImpl->MinRange = From->GetMinRange();
			ToImpl->MaxRange = From->GetMaxRange();
			return true;
		}
	}
	return false;
}