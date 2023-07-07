// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Sequence/Params/Shot/Point/CsParams_PointSequenceWeapon_Shot_Point.h"
#include "Point/Sequence/Params/Start/CsParams_PointSequenceWeapon_Start.h"

#include "CsData_PointSequenceWeapon.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
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

				#define PointsPerShotParamsType NCsWeapon::NPoint::NSequence::NShot::NPoint::FParams
				#define StartParamsType NCsWeapon::NPoint::NSequence::NStart::FParams

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
					* Get any information related to the Start location.
					* 
					* return
					*/
					virtual const StartParamsType& GetStartParams() const = 0;

				#undef PointsPerShotParamsType
				#undef StartParamsType
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointSequenceWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_PointSequenceWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define PointsPerShotParamsType NCsWeapon::NPoint::NSequence::NShot::NPoint::FParams
#define StartParamsType NCsWeapon::NPoint::NSequence::NStart::FParams

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
	* Get any information related to the Start location.
	*
	* return
	*/
	virtual const StartParamsType& GetStartParams() const = 0;

#undef PointsPerShotParamsType
#undef StartParamsType
};