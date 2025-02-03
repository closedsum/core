// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"

// Containers
#include "Containers/CsLibrary_InterfaceMap.h"

// DataType (NCsWeapon::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)

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
					using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;

					struct CSWP_API FLibrary final : public NCsInterfaceMap::TLibrary<ParamsType>
					{
					private:

						using DataType = NCsWeapon::NData::IData;
						using LocationType = NCsWeapon::NProjectile::NParams::NLaunch::ELocation;
						using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::EDirection;

					public:

						static bool IsValidChecked(const FString& Context, const ParamsType* Params);

						static const ParamsType* GetChecked(const FString& Context, const DataType* Data);
						
						static const LocationType& GetLocationTypeChecked(const FString& Context, const DataType* Data);
				
						static const DirectionType& GetDirectionTypeChecked(const FString& Context, const DataType* Data);
					};
				}
			}
		}
	}
}