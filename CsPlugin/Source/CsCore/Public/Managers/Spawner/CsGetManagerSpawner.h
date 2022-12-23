// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
#include "CsGetManagerSpawner.generated.h"

class UCsManager_Spawner;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Spawner* GetManager_Spawner() const = 0;

	virtual void SetManager_Spawner(UCsManager_Spawner* InManager) = 0;
};