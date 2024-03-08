// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsDataRootSet.h"

#include "CsGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsDataRootSet& GetCsDataRootSet() const = 0;
};