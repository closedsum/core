// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Projectile.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		/**
		*/
		struct CSPRJ_API IData : public ICsGetInterfaceMap
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
class CSPRJ_API UCsData_Projectile : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsData_Projectile : public ICsGetInterfaceMap
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