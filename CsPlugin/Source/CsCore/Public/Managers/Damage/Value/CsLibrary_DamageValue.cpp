// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointProxy.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeProxy.h"

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

			CS_IS_PTR_NULL_CHECKED(To)

			// Point
			{
				typedef NCsDamage::NValue::NPoint::IPoint PointType;

				if (const PointType* IFromPoint = GetSafeInterfaceChecked<PointType>(Context, From))
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

				if (const RangeType* IFromRange = GetSafeInterfaceChecked<RangeType>(Context, From))
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
			checkf(0, TEXT("%s: Failed to copy From to To."), *Context);
			return false;
		}

		#undef ValueType
	}
}