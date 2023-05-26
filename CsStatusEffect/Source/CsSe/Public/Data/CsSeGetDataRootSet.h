// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsSeDataRootSet.h"

#include "CsSeGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSSE_API UCsSeGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSE_API ICsSeGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsSeDataRootSet& GetCsSeDataRootSet() const = 0;
};