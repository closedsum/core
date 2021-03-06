// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/StaticMesh/Data/CsData_StaticMeshActor.h"

struct FCsInterfaceMap;

struct CSCORE_API FCsData_StaticMeshActorImpl : public ICsData_StaticMeshActor
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