// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsRequestEndPlayMap.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSPIE_API UCsRequestEndPlayMap : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPIE_API ICsRequestEndPlayMap
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void RequestEndPlayMapImpl() = 0;

};