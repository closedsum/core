// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

namespace NCsDamage
{
	namespace NData
	{
		#define DataType NCsDamage::NData::IData

		FString FLibrary::PrintDataAndClass(const DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("Data: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
			return FString::Printf(TEXT("Data: %s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
		}

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Data->GetValue())

			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL(Data)

			CS_IS_PTR_NULL(Data->GetValue())

			return true;
		}

		#define RangeType NCsDamage::NRange::IRange
		
		const RangeType* FLibrary::GetRangeChecked(const FString& Context, const DataType* Data)
		{
			CS_IS_PTR_NULL_CHECKED(Data)

			// ShapeDataType (NCsDamage::NData::NShape::IShape)
			{
				typedef NCsDamage::NData::NShape::IShape ShapeDataType;

				if (const ShapeDataType* Shape = GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					return Shape->GetRange();
				}
			}
			checkf(0, TEXT("%s: Failed to get RangeType (NCsDamage::NRange::IRange) from Data."), *Context);
			return nullptr;
		}

		const RangeType* FLibrary::GetSafeRange(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Data)

			// ShapeDataType (NCsDamage::NData::NShape::IShape)
			{
				typedef NCsDamage::NData::NShape::IShape ShapeDataType;

				if (const ShapeDataType* Shape = GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					return Shape->GetRange();
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get RangeType (NCsDamage::NRange::IRange) from Data."), *Context));
			return nullptr;
		}

		#undef RangeType

		#undef DataType
	}
}