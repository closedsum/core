// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsUIDataRootSet.h"

#include "CsUIGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsUIGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsUIGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsUIDataRootSet& GetCsUIDataRootSet() const = 0;
};