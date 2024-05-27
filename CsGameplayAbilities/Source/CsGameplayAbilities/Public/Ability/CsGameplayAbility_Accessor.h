// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsGameplayAbility_Accessor.generated.h"

UINTERFACE(Blueprintable)
class CSGAMEPLAYABILITIES_API UCsGameplayAbility_Accessor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSGAMEPLAYABILITIES_API ICsGameplayAbility_Accessor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const bool& CanRetriggerInstancedAbility() const = 0;
};