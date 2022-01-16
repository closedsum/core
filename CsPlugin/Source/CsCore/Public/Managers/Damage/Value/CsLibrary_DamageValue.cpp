// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Value/Copy/CsDamageValue_Copy.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"

namespace NCsDamage
{
	namespace NValue
	{
		#define ValueType NCsDamage::NValue::IValue

		const FECsDamageValue& FLibrary::GetTypeChecked(const FString& Context, const ValueType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Value)

			typedef NCsDamage::NValue::FLibrary ValueLibrary;
			typedef NCsDamage::NValue::NPoint::IPoint PointType;
			typedef NCsDamage::NValue::NRange::IRange RangeType;

			// Point
			if (GetSafeInterfaceChecked<PointType>(Context, Value))
				return NCsDamageValue::Point;
			// Range
			if (GetSafeInterfaceChecked<RangeType>(Context, Value))
				return NCsDamageValue::Range;

			checkf(0, TEXT("%s: Failed to determine type (FECsDamageValue) for Value."), *Context);
			return EMCsDamageValue::Get().GetMAX();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ValueType* From, ValueType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NValue::NCopy::ICopy CopyType;

			CopyType* Copy = GetInterfaceChecked<CopyType>(Context, To);

			Copy->Copy(From);
			return true;
		}

		#undef ValueType
	}
}