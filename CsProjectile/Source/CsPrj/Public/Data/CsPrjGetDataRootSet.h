// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsPrjDataRootSet.h"

#include "CsPrjGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsPrjGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsPrjGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsPrjDataRootSet& GetCsPrjDataRootSet() const = 0;
};