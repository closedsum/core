// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Process/Payload/CsProcessDamageDataPayload.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
	// Data
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NProcess
		{
			using ShapeDataType = NCsDamage::NData::NShape::IShape;
			using ValueType = NCsDamage::NValue::IValue;
			using RangeType = NCsDamage::NRange::IRange;

			void FPayload::SetTypeChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& InType)
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, InType)

				Type = InType;
				Data  = CsDamageManagerLibrary::GetDataChecked(Context, WorldContext, Type);
				Value = const_cast<ValueType*>(Data->GetValue());

				if (ShapeDataType* ShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					RangeType* _Range = const_cast<RangeType*>(ShapeData->GetRange());

					CS_IS_PTR_NULL_CHECKED(_Range)

					SetRange(_Range);
				}
			}
		}
	}
}