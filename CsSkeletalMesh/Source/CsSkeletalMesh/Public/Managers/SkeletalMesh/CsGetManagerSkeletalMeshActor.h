// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerSkeletalMeshActor.generated.h"

class UCsManager_SkeletalMeshActor;

UINTERFACE(Blueprintable)
class CSSKELETALMESH_API UCsGetManagerSkeletalMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
*/
class CSSKELETALMESH_API ICsGetManagerSkeletalMeshActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_SkeletalMeshActor* GetManager_SkeletalMeshActor() const = 0;

	virtual void SetManager_SkeletalMeshActor(UCsManager_SkeletalMeshActor* InManager) = 0;
};