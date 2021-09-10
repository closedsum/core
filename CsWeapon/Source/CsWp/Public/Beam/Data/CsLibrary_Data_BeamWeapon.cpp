// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Data/CsLibrary_Data_BeamWeapon.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Beam/Data/CsData_BeamWeapon.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NData
		{
			#define DataType NCsWeapon::NBeam::NData::IData

			bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL_CHECKED(Data)
				
				if (!Data->HasInfiniteCharge())
				{
					// Check MaxCharge is Valid
					CS_IS_INT_GREATER_THAN_CHECKED(Data->GetMaxCharge(), 0)
					// Check ChargeConsumedByShot is Valid
					CS_IS_INT_GREATER_THAN_CHECKED(Data->GetChargeConsumedByShot(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Data->GetTimeBetweenShots(), 0.0f)
				// Check BeamsPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Data->GetBeamsPerShot(), 1)
				// Check TimeBetweenBeamsPerShot is valid when BeamsPerShot > 1
				if (Data->GetBeamsPerShot() > 1)
				{
					checkf(Data->GetTimeBetweenBeamsPerShot() > 0.0f, TEXT("%s: TimeBetweenBeamsPerShot must be > 0.0f when BeamsPerShot > 1."), *Context);
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL(Data)
				
				if (!Data->HasInfiniteCharge())
				{
					// Check MaxAmmo is a Valid
					CS_IS_INT_GREATER_THAN(Data->GetMaxCharge(), 0)
					// Check ChargeConsumedByShot is Valid
					CS_IS_INT_GREATER_THAN(Data->GetChargeConsumedByShot(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN(Data->GetTimeBetweenShots(), 0.0f)
				// Check BeamsPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL(Data->GetBeamsPerShot(), 1)
				// Check TimeBetweenBeamsPerShot is valid when BeamsPerShot > 1
				if (Data->GetBeamsPerShot() > 1)
				{
					if (Data->GetTimeBetweenBeamsPerShot() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TimeBetweenBeamsPerShot must be > 0.0f when BeamsPerShot > 1."), *Context));
						return false;
					}
				}
				return true;
			}

			#undef DataType
		}
	}
}