// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerSpawner.generated.h"

class UCsManager_Spawner;

UINTERFACE(Blueprintable)
class CSSPAWNER_API UCsGetManagerSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSPAWNER_API ICsGetManagerSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Spawner* GetManager_Spawner() const = 0;

	virtual void SetManager_Spawner(UCsManager_Spawner* InManager) = 0;
};