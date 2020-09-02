// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Types/CsTypes_Collision.h"
#include "CsData_ProjectileCollision.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileCollision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any collision associated with a Projectile.
*/
class CSPRJ_API ICsData_ProjectileCollision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

	/**
	*
	*/
	virtual const float& GetCollisionRadius() const = 0;
};