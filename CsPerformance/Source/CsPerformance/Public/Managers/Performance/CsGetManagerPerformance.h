// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerPerformance.generated.h"

class UCsManager_Performance;

UINTERFACE(Blueprintable)
class CSPERFORMANCE_API UCsGetManagerPerformance : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPERFORMANCE_API ICsGetManagerPerformance
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Performance* GetManager_Performance() const = 0;

	virtual void SetManager_Performance(UCsManager_Performance* InManager) = 0;
};