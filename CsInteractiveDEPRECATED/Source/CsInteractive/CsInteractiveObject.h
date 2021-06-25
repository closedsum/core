// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Types
#include "CsTypes_InteractiveObject.h"
#include "CsInteractiveObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSINTERACTIVE_API UCsInteractiveObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
* OnHold
*
*/
DECLARE_MULTICAST_DELEGATE(FCsInteractiveObject_OnHold);

class CSINTERACTIVE_API ICsInteractiveObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Freeze() = 0;

	virtual void UnFreeze() = 0;

	/**
	*
	*
	* @param Params
	*/
	virtual void Hold(ICsInteractiveObjectHoldParams* Params) = 0;

	virtual FCsInteractiveObject_OnHold& GetOnHold_Event() const  = 0;

	/**
	*
	*
	* @param Params
	*/
	virtual void Release(ICsInteractiveObjectReleaseParams* Params) = 0;

	virtual void Touch() = 0;

	virtual void Hover() = 0;

	virtual void UnHover() = 0;

	virtual void Collide() = 0;

	virtual void UnCollide() = 0;

	virtual void Remove() = 0;
};