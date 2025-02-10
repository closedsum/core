// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Range/CsLibrary_DamageRange.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Range/Copy/CsDamageRange_Copy.h"

namespace NCsDamage
{
	namespace NRange
	{
		namespace NLibrary
		{
			using CopyType = NCsDamage::NRange::NCopy::ICopy;

			bool FLibrary::IsValidChecked(const FString& Context, const RangeType* Range)
			{
				CS_IS_PTR_NULL_CHECKED(Range)

				const float& MinRange = Range->GetMinRange();
				const float& MaxRange = Range->GetMaxRange();

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinRange, 0.0f)
				CS_IS_FLOAT_GREATER_THAN_CHECKED(MaxRange, MinRange)
				return true;
			}

		
			bool FLibrary::CopyChecked(const FString& Context, const RangeType* From, RangeType* To)
			{
				CopyType* ToC = GetInterfaceChecked<CopyType>(Context, To);

				check(ImplementsChecked<CopyType>(Context, From));

				ToC->Copy(From);
				return true;
		}
		}
	}
}