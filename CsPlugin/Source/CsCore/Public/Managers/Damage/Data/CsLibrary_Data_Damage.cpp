// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"

// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

#define RangeType NCsDamage::NRange::IRange
#define DataType NCsDamage::NData::IData
const RangeType* FCsLibrary_Data_Damage::GetRangeChecked(const FString& Context, const DataType* Data)
{
#undef RangeType
#undef DataType

	// NCsDamage::NData::NShape::IShape
	{
		typedef NCsDamage::NData::NShape::IShape ShapeDataType;

		if (const ShapeDataType* Shape = GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
		{
			return Shape->GetRange();
		}
	}
	return nullptr;
}