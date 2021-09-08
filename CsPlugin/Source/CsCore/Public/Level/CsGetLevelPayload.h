// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Load.h"

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