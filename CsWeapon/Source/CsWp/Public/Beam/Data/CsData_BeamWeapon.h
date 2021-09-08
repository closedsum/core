// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_BeamWeapon.generated.h"

// NCsWeapon::NBeam::NParams::NBeam::IBeam
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, IBeam)

namespace NCsWeapon
{
	namespace NBeam
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
				virtual const bool& HasInfiniteCharge() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetMaxCharge() const = 0;

				/**
				* 
				* 
				* return
				*/
				virtual const float& GetChargeConsumedByShot() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const int32& GetBeamsPerShot() const = 0;

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
				virtual const float& GetTimeBetweenBeamsPerShot() const = 0;

			#define BeamParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam

				/**
				*/
				virtual const BeamParamsType* GetBeamParams() const = 0;

			#undef BeamParamsType
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_BeamWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NBeam::NParams::NBeam::IBeam
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, IBeam)

/**
*
*/
class CSWP_API ICsData_BeamWeapon : public ICsGetInterfaceMap
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
	virtual const bool& HasInfinitCharge() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetMaxCharge() const = 0;

	/**
	* 
	* 
	* return
	*/
	virtual const float& GetChargeConsumedByShot() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetBeamsPerShot() const = 0;

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
	virtual const float& GetTimeBetweenBeamsPerShot() const = 0;

#define BeamParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam

	/**
	*/
	virtual const BeamParamsType* GetBeamParams() const = 0;

#undef BeamParamsType
};