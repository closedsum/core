// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
			void FPayload::SetTypeChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& InType)
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, InType)

				Type = InType;

				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
				typedef NCsDamage::NData::FLibrary DataLibrary;
				typedef NCsDamage::NData::NShape::IShape ShapeDataType;
				typedef NCsDamage::NValue::IValue ValueType;

				Data  = DamageManagerLibrary::GetDataChecked(Context, WorldContext, Type);
				Value = const_cast<ValueType*>(Data->GetValue());

				if (ShapeDataType* ShapeData = DataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					typedef NCsDamage::NRange::IRange RangeType;

					RangeType* _Range = const_cast<RangeType*>(ShapeData->GetRange());

					CS_IS_PTR_NULL_CHECKED(_Range)

					SetRange(_Range);
				}
			}
		}
	}
}