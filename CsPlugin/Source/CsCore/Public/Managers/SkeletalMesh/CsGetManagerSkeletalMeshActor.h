// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerSkeletalMeshActor.generated.h"

class UCsManager_SkeletalMeshActor;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerSkeletalMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
*/
class CSCORE_API ICsGetManagerSkeletalMeshActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_SkeletalMeshActor* GetManager_SkeletalMeshActor() const = 0;

	virtual void SetManager_SkeletalMeshActor(UCsManager_SkeletalMeshActor* InManager) = 0;
};