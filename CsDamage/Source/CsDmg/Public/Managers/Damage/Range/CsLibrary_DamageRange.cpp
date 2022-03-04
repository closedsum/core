// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "CsDmg.h"

// Damage
#include "Managers/Damage/Range/Copy/CsDamageRange_Copy.h"

namespace NCsDamage
{
	namespace NRange
	{
		#define RangeType NCsDamage::NRange::IRange
		bool FLibrary::CopyChecked(const FString& Context, const RangeType* From, RangeType* To)
		{
		#undef RangeType

			typedef NCsDamage::NRange::NCopy::ICopy CopyType;

			CopyType* ToC = GetInterfaceChecked<CopyType>(Context, To);

			check(ImplementsChecked<CopyType>(Context, From));

			ToC->Copy(From);
			return true;
		}
	}
}