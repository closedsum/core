// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsShutdown.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsShutdown : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsShutdown
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Shutdown() = 0;
};