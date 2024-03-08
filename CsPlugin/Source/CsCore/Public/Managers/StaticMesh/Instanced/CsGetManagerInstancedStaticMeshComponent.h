// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerInstancedStaticMeshComponent.generated.h"

class ACsManager_InstancedStaticMeshComponent;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerInstancedStaticMeshComponent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
*/
class CSCORE_API ICsGetManagerInstancedStaticMeshComponent
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ACsManager_InstancedStaticMeshComponent* GetManager_InstancedStaticMeshComponent() const = 0;

	virtual void SetManager_InstancedStaticMeshComponent(ACsManager_InstancedStaticMeshComponent* InManager) = 0;
};