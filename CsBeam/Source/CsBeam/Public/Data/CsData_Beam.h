// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Beam.generated.h"

namespace NCsBeam
{
	namespace NData
	{
		/**
		*/
		struct CSBEAM_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

			/**
			*
			*
			* return
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const float& GetInitialSpeed() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const float& GetMaxSpeed() const = 0;

			/**
			*
			*
			* return
			*/
			virtual const float& GetGravityScale() const = 0;
		};
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsData_Beam : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const float& GetLifeTime() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetInitialSpeed() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetMaxSpeed() const = 0;

	/**
	* 
	*
	* return
	*/
	virtual const float& GetGravityScale() const = 0;
};