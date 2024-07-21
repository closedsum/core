// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Enhanced/Data/CsEnhancedInputWithGameplayTagDataRootSet.h"

#include "CsGetEnhancedInputWithGameplayTagDataRootSet.generated.h"

UINTERFACE(BlueprintType)
class CSINPUTWITHGAMEPLAYTAG_API UCsGetEnhancedInputWithGameplayTagDataRootSet : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUTWITHGAMEPLAYTAG_API ICsGetEnhancedInputWithGameplayTagDataRootSet
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsEnhancedInputWithGameplayTagDataRootSet& GetCsEnhancedInputWithGameplayTagDataRootSet() const = 0;
};