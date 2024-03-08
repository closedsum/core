// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StatusEffect.h"

#include "CsData_StatusEffect.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		/**
		* Interface that describes the properties of a Status Effect, object
		* that implements the interface: NCsStatusEffect::IStatusEffect.
		*/
		struct CSSE_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IData(){}

			/**
			* Whether the Status EFfect should remain on the object or in the world.
			*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect 
			* NOTE: The duration of the Status Effect (i.e. LifeTime) is part of another interface.
			* 
			* return
			*/
			virtual const bool& IsPersistent() const = 0;

			/**
			* Additional Status Effects to apply when the current Status Effect based on this 
			* data is applied.
			*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
			*
			* return
			*/
			virtual const TArray<FECsStatusEffect>& GetChildren() const = 0;

			/**
			* Status Effects to remove when the current Status Effect based on this data is applied.
			*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
			* 
			* return
			*/
			virtual const TArray<FECsStatusEffect>& GetStatusEffectsToRemove() const = 0;
		};
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Whether the Status EFfect should remain on the object or in the world.
	*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect 
	* NOTE: The duration of the Status Effect (i.e. LifeTime) is part of another interface.
	* 
	* return
	*/
	virtual const bool& IsPersistent() const = 0;

	/**
	* Additional Status Effect to apply when the current Status Effect based on this
	* data is applied.
	*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
	*
	* return
	*/
	virtual const TArray<FECsStatusEffect>& GetChildren() const = 0;

	/**
	* Status Effects to remove when the current Status Effect based on this data is applied.
	*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
	*
	* return
	*/
	virtual const TArray<FECsStatusEffect>& GetStatusEffectsToRemove() const = 0;
};