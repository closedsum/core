// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_DamageOrientation.generated.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NOrientation
		{
			/**
			* Interface to any orientation (Location, Rotation, ... etc) related information to Damage.
			*  This interface is "layered" on top of a "base" interface: NCsDamage::NData::IData.
			*/
			struct CSDMG_API IOrientation : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IOrientation(){}

				/**
				* Get the Translation Offset to apply to the Base Location.
				* 
				* return Location
				*/
				virtual const FVector& GetLocation() const = 0;

				/** 
				* Get the Rotation Offset to apply to the Direction.
				*  Pitch rotates Direction about the Right Vector with respect to Direction.
				*  Yaw rotates Direction about the World Up Vector.
				*  Roll is NOT used. 
				* 
				* return Rotation.
				*/
				virtual const FRotator& GetRotation() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_DamageOrientation : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to any orientation (Location, Rotation, ... etc) related information to Damage.
*  This interface is "layered" on top of a "base" interface: ICsData_Damage.
*/
class CSDMG_API ICsData_DamageOrientation : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Get the Translation Offset to apply to the Base Location.
	*
	* return Location
	*/
	virtual const FVector& GetLocation() const = 0;

	/**
	* Get the Rotation Offset to apply to the Direction.
	*  Pitch rotates Direction about the Right Vector with respect to Direction.
	*  Yaw rotates Direction about the World Up Vector.
	*  Roll is NOT used.
	*
	* return Rotation.
	*/
	virtual const FRotator& GetRotation() const = 0;
};