// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_ProjectileWeapon.generated.h"

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			/**
			*
			*/
			struct CSWP_API IData : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

			public:

				virtual ~IData(){}

				/**
				*
				*
				* return
				*/
				virtual const bool& DoFireOnRelease() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const bool& IsFullAuto() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const bool& HasInfiniteAmmo() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const int32& GetMaxAmmo() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const int32& GetProjectilesPerShot() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenShots() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenAutoShots() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenProjectilesPerShot() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const LaunchParamsType* GetLaunchParams() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

/**
*
*/
class CSWP_API ICsData_ProjectileWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual const bool& DoFireOnRelease() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& IsFullAuto() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& HasInfiniteAmmo() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetMaxAmmo() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetProjectilesPerShot() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenShots() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenAutoShots() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenProjectilesPerShot() const = 0;

	typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

	/**
	*
	*
	* return
	*/
	virtual const LaunchParamsType* GetLaunchParams() const = 0;
};