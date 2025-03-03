// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_StaticMeshActor.generated.h"

UINTERFACE(BlueprintType)
class CSSTATICMESH_API UCsData_StaticMeshActor : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSTATICMESH_API ICsData_StaticMeshActor : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};