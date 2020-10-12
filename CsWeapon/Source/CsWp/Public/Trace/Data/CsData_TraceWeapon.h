// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_TraceWeapon.generated.h"

namespace NCsWeapon
{
	namespace NTrace
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
				virtual const int32& GetTracesPerShot() const = 0;

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
				virtual const float& GetTimeBetweenTracesPerShot() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_TraceWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_TraceWeapon : public ICsGetInterfaceMap
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
	virtual const int32& GetTracesPerShot() const = 0;

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
	virtual const float& GetTimeBetweenTracesPerShot() const = 0;
};