// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Params/Shot/Point/CsParams_PointWeapon_Shot_Point.h"
#include "Point/Params/Spread/CsParams_PointWeapon_Spread.h"

#include "CsData_PointWeapon.generated.h"

namespace NCsWeapon
{
	namespace NPoint
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

			public:

				virtual ~IData(){}

			#define PointsPerShotParamsType NCsWeapon::NPoint::NShot::NPoint::FParams
			#define SpreadParamsType NCsWeapon::NPoint::NSpread::FParams

				/**
				* Get whether to perform a Fire action on input pressed or released.
				*
				* return
				*/
				virtual const bool& DoFireOnRelease() const = 0;

				/**
				* Get whether the Fire action continues to execute when the Fire action is
				* active.
				*
				* return
				*/
				virtual const bool& IsFullAuto() const = 0;

				/**
				* Get whether the weapon uses infinite ammo.
				*  Max Ammo is ignored if TRUE.
				*
				* return
				*/
				virtual const bool& HasInfiniteAmmo() const = 0;

				/**
				* Get the maximum amount ammo that can be consumed before the Fire action
				* can NO longer be called.
				*
				* return
				*/
				virtual const int32& GetMaxAmmo() const = 0;

				/**
				* Get the minimum interval of time in seconds between executing the Fire action.
				*
				* return
				*/
				virtual const float& GetTimeBetweenShots() const = 0;

				/**
				* Get the minimum interval of time in seconds between automatically executing the Fire action.
				* This is only valid if IsFullAuto() is TRUE.
				*
				* return
				*/
				virtual const float& GetTimeBetweenAutoShots() const = 0;

				/**
				* Get any information related to Points per Shot.
				*
				* return
				*/
				virtual const PointsPerShotParamsType& GetPointsPerShotParams() const = 0;

				/**
				* Get whether to use Spread Params or not.
				*
				* return
				*/
				virtual const bool& UseSpreadParams() const = 0;

				/**
				* Get any information related to Spread Shape.
				*  NOTE: UseSpreadParams() must be TRUE for this to be used.
				*
				* return
				*/
				virtual const SpreadParamsType& GetSpreadParams() const = 0;

			#undef PointsPerShotParamsType
			#undef SpreadParamsType
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_PointWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define PointsPerShotParamsType NCsWeapon::NPoint::NShot::NPoint::FParams
#define SpreadParamsType NCsWeapon::NPoint::NSpread::FParams

	/**
	* Get whether to perform a Fire action on input pressed or released.
	*
	* return
	*/
	virtual const bool& DoFireOnRelease() const = 0;

	/**
	* Get whether the Fire action continues to execute when the Fire action is
	* active.
	*
	* return
	*/
	virtual const bool& IsFullAuto() const = 0;

	/**
	* Get whether the weapon uses infinite ammo.
	*  Max Ammo is ignored if TRUE.
	*
	* return
	*/
	virtual const bool& HasInfiniteAmmo() const = 0;

	/**
	* Get the maximum amount ammo that can be consumed before the Fire action
	* can NO longer be called.
	*
	* return
	*/
	virtual const int32& GetMaxAmmo() const = 0;

	/**
	* Get the minimum interval of time in seconds between executing the Fire action.
	*
	* return
	*/
	virtual const float& GetTimeBetweenShots() const = 0;

	/**
	* Get the minimum interval of time in seconds between automatically executing the Fire action.
	* This is only valid if IsFullAuto() is TRUE.
	*
	* return
	*/
	virtual const float& GetTimeBetweenAutoShots() const = 0;

	/** 
	* Get any information related to Points per Shot.
	* 
	* return
	*/
	virtual const PointsPerShotParamsType& GetPointsPerShotParams() const = 0;

	/**
	* Get whether to use Spread Params or not.
	* 
	* return
	*/
	virtual const bool& UseSpreadParams() const = 0;

	/**
	* Get any information related to Spread Shape.
	*  NOTE: UseSpreadParams() must be TRUE for this to be used.
	* 
	* return
	*/
	virtual const SpreadParamsType& GetSpreadParams() const = 0;

#undef PointsPerShotParamsType
#undef SpreadParamsType
};