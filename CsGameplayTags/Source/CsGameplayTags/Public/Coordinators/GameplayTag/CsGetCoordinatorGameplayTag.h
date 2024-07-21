// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetCoordinatorGameplayTag.generated.h"

class UCsCoordinator_GameplayTag;

UINTERFACE(Blueprintable)
class CSGAMEPLAYTAGS_API UCsGetCoordinatorGameplayTag : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSGAMEPLAYTAGS_API ICsGetCoordinatorGameplayTag
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoordinator_GameplayTag* GetCoordinator_GameplayTag() const = 0;

	virtual void SetCoordinator_GameplayTag(UCsCoordinator_GameplayTag* InCoordinator) = 0;
};