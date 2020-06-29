// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Types/CsTypes_AttachDetach.h"
#pragma once

struct CSCORE_API ICsFXPooledPayload : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsFXPooledPayload(){}

	/**
	* Get the Attachment Transform Rule when attaching the FX to the 
	* Parent. If the Parent is NULL, the FX will NOT be attached.
	*
	* return Attachment Rule
	*/
	//virtual const ECsAttachmentTransformRules& GetAttachmentTransformRule() const;

	/**
	* Get the Transform to apply to the FX. If the FX is being attached to the
	* Parent, apply the transform after the attachment. Usually this will be applied
	* as a world transform.
	*
	* return Transform
	*/
	//virtual const FTransform& GetTransform() const;
};