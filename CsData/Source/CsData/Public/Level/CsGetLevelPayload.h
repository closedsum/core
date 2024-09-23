// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsTypes_Payload.h"

#include "CsGetLevelPayload.generated.h"

UINTERFACE(BlueprintType)
class CSDATA_API UCsGetLevelPayload : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSDATA_API ICsGetLevelPayload
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsPayload& GetLevelPayload() const = 0;
};