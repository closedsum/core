// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Time/CsTypes_Update.h"

#include "CsGetUpdateGroup.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTIME_API UCsGetUpdateGroup : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSTIME_API ICsGetUpdateGroup
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FECsUpdateGroup& GetUpdateGroup() const = 0;
};