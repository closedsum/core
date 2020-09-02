// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"

bool FCsLibrary_DamageValue::CopyChecked(const FString& Context, const ICsDamageValue* From, ICsDamageValue* To)
{
	// Point
	if (ICsDamageValuePoint* IFromPoint = GetSafeInterfaceChecked<ICsDamageValuePoint>(Context, const_cast<ICsDamageValue*>(From)))
	{
		// FCsDamageValuePointImpl (ICsDamageValuePoint)
		if (FCsDamageValuePointImpl* ToImpl = SafePureStaticCastChecked<FCsDamageValuePointImpl>(Context, To))
		{
			ToImpl->Value = IFromPoint->GetValue();
			return true;
		}
	}
	// Range
	if (ICsDamageValueRange* IFromRange = GetSafeInterfaceChecked<ICsDamageValueRange>(Context, const_cast<ICsDamageValue*>(From)))
	{
		// FCsDamageValuePointImpl (ICsDamageValuePoint)
		if (FCsDamageValueRangeImpl* ToImpl = SafePureStaticCastChecked<FCsDamageValueRangeImpl>(Context, To))
		{
			ToImpl->MinValue = IFromRange->GetMinValue();
			ToImpl->MaxValue = IFromRange->GetMaxValue();
			return true;
		}
	}
	return false;
}