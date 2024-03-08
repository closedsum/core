// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerStaticMeshActor.generated.h"

class UCsManager_StaticMeshActor;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerStaticMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
*/
class CSCORE_API ICsGetManagerStaticMeshActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_StaticMeshActor* GetManager_StaticMeshActor() const = 0;

	virtual void SetManager_StaticMeshActor(UCsManager_StaticMeshActor* InManager) = 0;
};