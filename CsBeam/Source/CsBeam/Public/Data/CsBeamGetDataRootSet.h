// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsBeamDataRootSet.h"

#include "CsBeamGetDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSBEAM_API UCsBeamGetDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsBeamGetDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsBeamDataRootSet& GetCsBeamDataRootSet() const = 0;
};