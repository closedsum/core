// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/SkeletalMesh/Data/CsData_SkeletalMeshActor.h"

struct FCsInterfaceMap;

struct CSSKELETALMESH_API FCsData_SkeletalMeshActorImpl : public ICsData_SkeletalMeshActor
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_SkeletalMeshActorImpl();
	~FCsData_SkeletalMeshActorImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_SkeletalMeshActor
#pragma region
public:

#pragma endregion ICsData_SkeletalMeshActor
};