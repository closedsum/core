// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Types/Property/Ref/CsProperty_Ref_float.h"
#include "CsData_Projectile.generated.h"

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