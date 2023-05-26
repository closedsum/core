// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"

// Containers
#include "Containers/CsLibrary_InterfaceMap.h"

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
			#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch

				struct CSWP_API FLibrary final : public NCsInterfaceMap::TLibrary<ParamsType>
				{
				public:

				#define DataType NCsWeapon::NData::IData

					static bool IsValidChecked(const FString& Context, const ParamsType* Params);

					static const ParamsType* GetChecked(const FString& Context, const DataType* Data);

				#define LocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation		
					static const LocationType& GetLocationTypeChecked(const FString& Context, const DataType* Data);
				#undef LocationType

				#define DirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection
					static const DirectionType& GetDirectionTypeChecked(const FString& Context, const DataType* Data);
				#undef DirectionType

				#undef DataType
				};

			#undef ParamsType
			}
		}
	}
}