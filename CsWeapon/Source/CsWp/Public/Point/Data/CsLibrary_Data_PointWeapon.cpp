// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/CsLibrary_Data_PointWeapon.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Point/Data/CsData_PointWeapon.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NData
		{
			#define DataType NCsWeapon::NPoint::NData::IData

			bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL_CHECKED(Data)
				// Check MaxAmmo is a valid value
				if (!Data->HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN_CHECKED(Data->GetMaxAmmo(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Data->GetTimeBetweenShots(), 0.0f)
				// Check ProjectilePerShot
				CS_IS_VALID_CHECKED(Data->GetPointsPerShotParams());
				// Check Start
				CS_IS_VALID_CHECKED(Data->GetStartParams());
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL(Data)
				// Check MaxAmmo is a valid value
				if (!Data->HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN(Data->GetMaxAmmo(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Data->GetTimeBetweenShots(), 0.0f)
				// Check ProjectilePerShot
				CS_IS_VALID(Data->GetPointsPerShotParams())
				// Check Start
				CS_IS_VALID(Data->GetStartParams())
				return true;
			}

			#undef DataType
		}
	}
}