// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsDmgDataRootSet.h"

#include "CsDmgGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSDMG_API UCsDmgGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSDMG_API ICsDmgGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsDmgDataRootSet& GetCsDmgDataRootSet() const = 0;
};