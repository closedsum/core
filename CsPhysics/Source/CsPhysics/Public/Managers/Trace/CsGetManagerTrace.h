// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerTrace.generated.h"

class UCsManager_Trace;

UINTERFACE(Blueprintable)
class CSPHYSICS_API UCsGetManagerTrace : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPHYSICS_API ICsGetManagerTrace
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Trace* GetManager_Trace() const = 0;

	virtual void SetManager_Trace(UCsManager_Trace* InManager) = 0;
};