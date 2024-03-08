// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsWpDataRootSet.h"

#include "CsWpGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsWpGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsWpGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsWpDataRootSet& GetCsWpDataRootSet() const = 0;
};