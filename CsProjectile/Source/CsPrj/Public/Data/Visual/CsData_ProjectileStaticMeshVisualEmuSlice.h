// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/Visual/CsData_ProjectileStaticMeshVisual.h"

struct FCsInterfaceMap;
struct FCsPrjStaticMesh;

/**
*/
struct CSPRJ_API FCsData_ProjectileStaticMeshVisualEmuSlice final : public ICsData_ProjectileStaticMeshVisual
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	// ICsData_ProjectileStaticMeshVisual

	FCsPrjStaticMesh* StaticMesh;

public:

	FCsData_ProjectileStaticMeshVisualEmuSlice();
	~FCsData_ProjectileStaticMeshVisualEmuSlice();

public:

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
	{
		InterfaceMap = Map;
	}

// ICsData_ProjectileVisual
#pragma region
public:

	FORCEINLINE const FCsPrjStaticMesh& GetStaticMesh() const 
	{
		return *StaticMesh;
	}

#pragma endregion ICsData_ProjectileVisual

public:

	FORCEINLINE void SetStaticMesh(FCsPrjStaticMesh* Value)
	{
		StaticMesh = Value;
	}
};