// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "CsTypes_Update.h"

#include "CsGetUpdateGroup.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsGetUpdateGroup : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSCORE_API ICsGetUpdateGroup
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FECsUpdateGroup& GetUpdateGroup() const = 0;
};