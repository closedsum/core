// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerTrace.generated.h"

class UCsManager_Trace;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerTrace : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerTrace
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Trace* GetManager_Trace() const = 0;

	virtual void SetManager_Trace(UCsManager_Trace* InManager) = 0;
};