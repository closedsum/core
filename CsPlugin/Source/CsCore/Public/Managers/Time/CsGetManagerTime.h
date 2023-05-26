// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerTime.generated.h"

class UCsManager_Time;

UINTERFACE(Blueprintable)
class UCsGetManagerTime : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerTime
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Time* GetManager_Time() const = 0;

	virtual void SetManager_Time(UCsManager_Time* InManager) = 0;
};