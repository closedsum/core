// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "UniqueObject/CsTypes_UniqueObject.h"

#include "CsUniqueObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTYPES_API UCsUniqueObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSTYPES_API ICsUniqueObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FCsUniqueObjectId& GetId() const = 0;
};