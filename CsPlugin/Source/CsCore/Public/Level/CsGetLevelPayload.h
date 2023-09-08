// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Data/CsTypes_Payload.h"

#include "CsGetLevelPayload.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsGetLevelPayload : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetLevelPayload
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