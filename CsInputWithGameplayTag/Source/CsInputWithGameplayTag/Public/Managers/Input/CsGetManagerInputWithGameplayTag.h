// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerInputWithGameplayTag.generated.h"

class ICsManager_Input_WithGameplayTag;

UINTERFACE(Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsGetManagerInputWithGameplayTag : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUTWITHGAMEPLAYTAG_API ICsGetManagerInputWithGameplayTag
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsManager_Input_WithGameplayTag* GetManager_Input_WithGameplayTag() const = 0;

	virtual void SetManager_Input_WithGameplayTag(ICsManager_Input_WithGameplayTag* InManager) = 0;
};