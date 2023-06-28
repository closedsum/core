// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"\

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