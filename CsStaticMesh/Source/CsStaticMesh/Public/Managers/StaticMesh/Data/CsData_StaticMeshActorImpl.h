// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/StaticMesh/Data/CsData_StaticMeshActor.h"

struct FCsInterfaceMap;

struct CSSTATICMESH_API FCsData_StaticMeshActorImpl : public ICsData_StaticMeshActor
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_StaticMeshActorImpl();
	~FCsData_StaticMeshActorImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_StaticMeshActor
#pragma region
public:

#pragma endregion ICsData_StaticMeshActor
};