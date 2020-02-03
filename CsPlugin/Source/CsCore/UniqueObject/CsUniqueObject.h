// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "CsUniqueObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsUniqueObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsUniqueObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FCsUniqueObjectId& GetId() = 0;
};