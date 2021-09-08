// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "CsUniqueObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsUniqueObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsUniqueObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FCsUniqueObjectId& GetId() const = 0;
};