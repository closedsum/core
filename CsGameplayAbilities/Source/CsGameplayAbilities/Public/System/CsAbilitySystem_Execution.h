// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"

#include "CsAbilitySystem_Execution.generated.h"

UINTERFACE(Blueprintable)
class CSGAMEPLAYABILITIES_API UCsAbilitySystem_Execution : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSGAMEPLAYABILITIES_API ICsAbilitySystem_Execution
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const TMap<FGameplayAbilitySpecHandle, FGameplayTagContainer>& GetExecutionRequiredTagsByAbilitySpecHandleMap() const = 0;

	virtual void AddExecutionRequiredTags(const FGameplayAbilitySpecHandle& Handle, const FGameplayTagContainer& Tags) = 0;

	virtual void RemoveExecutionRequiredTags(const FGameplayAbilitySpecHandle& Handle) = 0;
};