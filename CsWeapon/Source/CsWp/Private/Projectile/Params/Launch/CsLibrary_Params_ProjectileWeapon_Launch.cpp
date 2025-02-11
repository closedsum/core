// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsLibrary_Params_ProjectileWeapon_Launch.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NLibrary
				{
					using DataType = NCsWeapon::NData::IData;
					using PrjWeaponDataType = NCsWeapon::NProjectile::NData::IData;
					using LocationType = NCsWeapon::NProjectile::NParams::NLaunch::ELocation;
					using LocationMapType = NCsWeapon::NProjectile::NParams::NLaunch::EMLocation;
					using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::EDirection;
					using DirectionMapType = NCsWeapon::NProjectile::NParams::NLaunch::EMDirection;

					bool FLibrary::IsValidChecked(const FString& Context, const ParamsType* Params)
					{
						CS_IS_ENUM_VALID_CHECKED(LocationMapType, Params->GetLocationType())
						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Params->GetDirectionType())

						checkf(Params->GetDirectionRules() != NCsRotationRules::None, TEXT("%s: No DirectionRules set in Param."), *Context);
						return true;
					}

					const ParamsType* FLibrary::GetChecked(const FString& Context, const DataType* Data)
					{
						CS_IS_PTR_NULL_CHECKED(Data);

						const PrjWeaponDataType* WeaponData = CsWeaponDataLibrary::GetInterfaceChecked<PrjWeaponDataType>(Context, Data);
						const ParamsType* LaunchParams		= WeaponData->GetLaunchParams();

						check(IsValidChecked(Context, LaunchParams));
						return LaunchParams;
					}
			
					const LocationType& FLibrary::GetLocationTypeChecked(const FString& Context, const DataType* Data)
					{
						return GetChecked(Context, Data)->GetLocationType();
					}
				
					const DirectionType& FLibrary::GetDirectionTypeChecked(const FString& Context, const DataType* Data)
					{
						return GetChecked(Context, Data)->GetDirectionType();
					}
				}
			}
		}
	}
}