// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerAchievement.generated.h"

class UCsManager_Achievement;

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsGetManagerAchievement : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerAchievement
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Achievement* GetManager_Achievement() const = 0;

	virtual void SetManager_Achievement(UCsManager_Achievement* InManager) = 0;
};