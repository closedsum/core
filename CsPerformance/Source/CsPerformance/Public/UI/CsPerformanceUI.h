// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsPerformanceUI.generated.h"

UINTERFACE(Blueprintable)
class CSPERFORMANCE_API UCsPerformanceUI : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPERFORMANCE_API ICsPerformanceUI
{
	GENERATED_IINTERFACE_BODY()

	virtual void Init(UObject* InRoot) = 0;
};