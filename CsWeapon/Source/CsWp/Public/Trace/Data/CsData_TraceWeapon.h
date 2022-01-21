// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_TraceWeapon.generated.h"

// NCsWeapon::NTrace::NParams::NTrace::ITrace
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, ITrace)

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

			#define TraceParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace

				/**
				*/
				virtual const TraceParamsType* GetTraceParams() const = 0;

			#undef TraceParamsType
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_TraceWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NTrace::NParams::NTrace::ITrace
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NParams, NTrace, ITrace)

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

#define TraceParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace

	/**
	*/
	virtual const TraceParamsType* GetTraceParams() const = 0;

#undef TraceParamsType
};