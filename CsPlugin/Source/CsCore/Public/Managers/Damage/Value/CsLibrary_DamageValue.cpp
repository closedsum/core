// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsCore.h"

// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"

namespace NCsDamage
{
	namespace NValue
	{
		#define ValueType NCsDamage::NValue::IValue
		bool FLibrary::CopyChecked(const FString& Context, const ValueType* From, ValueType* To)
		{

			// Point
			{
				typedef NCsDamage::NValue::NPoint::IPoint PointType;

				if (PointType* IFromPoint = GetSafeInterfaceChecked<PointType>(Context, const_cast<ValueType*>(From)))
				{
					// NCsDamage::NValue::NPoint::FImpl (NCsDamage::NValue::NPoint::IPoint)
					typedef NCsDamage::NValue::NPoint::FImpl ImplType;

					if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
					{
						ToImpl->SetValue(IFromPoint->GetValue());
						return true;
					}
				}
			}
			// Range
			{
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
		#undef ValueType
	}
}