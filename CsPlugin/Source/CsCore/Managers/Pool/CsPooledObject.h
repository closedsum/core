// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsPooledObject.generated.h"

UINTERFACE(Blueprintable)
class UCsPooledObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsPooledObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsPooledObjectCache* GetCache() = 0;

	virtual void Allocate(ICsPooledObjectPayload* Payload) = 0;

	virtual void Deallocate() = 0;
};