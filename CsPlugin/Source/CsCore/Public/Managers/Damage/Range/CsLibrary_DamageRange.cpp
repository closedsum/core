// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Range/CsDamageRangeImpl.h"

#define RangeType NCsDamage::NRange::IRange
bool FCsLibrary_DamageRange::CopyChecked(const FString& Context, const RangeType* From, RangeType* To)
{
#undef RangeType
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