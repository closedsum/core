// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsLibrary_Data_ProjectileWeapon.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			#define DataType NCsWeapon::NProjectile::NData::IData

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
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Data->GetTimeBetweenShots(), 0.0f)
				// Check ProjectilePerShot
				CS_IS_VALID_CHECKED(Data->GetProjectilesPerShotParams());
				// Check Spread
				if (Data->UseSpreadParams())
				{
					CS_IS_VALID_CHECKED(Data->GetSpreadParams());
				}
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
				CS_IS_FLOAT_GREATER_THAN(Data->GetTimeBetweenShots(), 0.0f)
				// Check ProjectilePerShot
				CS_IS_VALID(Data->GetProjectilesPerShotParams())
				// Check Spread
				if (Data->UseSpreadParams())
				{
					CS_IS_VALID(Data->GetSpreadParams())
				}
				return true;
			}

			#undef DataType
		}
	}
}