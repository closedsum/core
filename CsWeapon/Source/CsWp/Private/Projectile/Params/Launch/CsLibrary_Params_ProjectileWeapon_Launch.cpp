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
			#define DataType NCsWeapon::NData::IData
			#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch

				bool FLibrary::IsValidChecked(const FString& Context, const ParamsType* Params)
				{
					typedef NCsWeapon::NProjectile::NParams::NLaunch::EMLocation LocationMapType;
					typedef NCsWeapon::NProjectile::NParams::NLaunch::EMDirection DirectionMapType;

					CS_IS_ENUM_VALID_CHECKED(LocationMapType, Params->GetLocationType())
					CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Params->GetDirectionType())

					checkf(Params->GetDirectionRules() != NCsRotationRules::None, TEXT("%s: No DirectionRules set in Param for %s."), *Context);
					return true;
				}

				const ParamsType* FLibrary::GetChecked(const FString& Context, const DataType* Data)
				{
					CS_IS_PTR_NULL_CHECKED(Data);

					typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					const PrjWeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<PrjWeaponDataType>(Context, Data);
					const ParamsType* LaunchParams		= WeaponData->GetLaunchParams();

					check(IsValidChecked(Context, LaunchParams));
					return LaunchParams;
				}

				#define LocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation
				const LocationType& FLibrary::GetLocationTypeChecked(const FString& Context, const DataType* Data)
				{
				#undef LocationType
					return GetChecked(Context, Data)->GetLocationType();
				}

				#define DirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection
				const DirectionType& FLibrary::GetDirectionTypeChecked(const FString& Context, const DataType* Data)
				{
				#undef DirectionType
					return GetChecked(Context, Data)->GetDirectionType();
				}

			#undef DataType
			#undef ParamsType
			}
		}
	}
}