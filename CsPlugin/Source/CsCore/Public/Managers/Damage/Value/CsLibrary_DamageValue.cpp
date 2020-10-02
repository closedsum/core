// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"

#define ValueType NCsDamage::NValue::IValue
bool FCsLibrary_DamageValue::CopyChecked(const FString& Context, const ValueType* From, ValueType* To)
{
#undef ValueType
	// Point
	{
		typedef NCsDamage::NValue::IValue ValueType;
		typedef NCsDamage::NValue::NPoint::IPoint PointType;

		if (PointType* IFromPoint = GetSafeInterfaceChecked<PointType>(Context, const_cast<ValueType*>(From)))
		{
			// NCsDamage::NValue::NPoint::FImpl (NCsDamage::NValue::NPoint::IPoint)
			typedef NCsDamage::NValue::NPoint::FImpl ImplType;

			if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
			{
				ToImpl->Value = IFromPoint->GetValue();
				return true;
			}
		}
	}
	// Range
	{
		typedef NCsDamage::NValue::IValue ValueType;
		typedef NCsDamage::NValue::NRange::IRange RangeType;

		if (RangeType* IFromRange = GetSafeInterfaceChecked<RangeType>(Context, const_cast<ValueType*>(From)))
		{
			// NCsDamage::NValue::NRange::FImpl (NCsDamage::NValue::NRange::IRange)
			typedef NCsDamage::NValue::NRange::FImpl ImplType;

			if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
			{
				ToImpl->MinValue = IFromRange->GetMinValue();
				ToImpl->MaxValue = IFromRange->GetMaxValue();
				return true;
			}
		}
	}
	return false;
}