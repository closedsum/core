// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/SkeletalMesh/Data/CsData_SkeletalMeshActor.h"

struct FCsInterfaceMap;

struct CSCORE_API FCsData_SkeletalMeshActorImpl : public ICsData_SkeletalMeshActor
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