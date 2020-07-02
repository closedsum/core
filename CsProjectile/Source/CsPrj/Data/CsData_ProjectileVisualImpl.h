// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_ProjectileVisual.h"

struct FCsInterfaceMap;
class UStaticMesh;
class USkeletalMesh;

/**
*/
struct CSPRJ_API FCsData_ProjectileVisualImpl final : public ICsData_ProjectileVisual
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	// ICsData_ProjectileVisual

	UStaticMesh** StaticMesh;

	USkeletalMesh** SkeletalMesh;

	FCsFX* TrailFX;

public:

	FCsData_ProjectileVisualImpl();
	~FCsData_ProjectileVisualImpl();

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

	FORCEINLINE UStaticMesh* GetStaticMesh() const 
	{
		return *StaticMesh;
	}

	FORCEINLINE USkeletalMesh* GetSkeletalMesh() const
	{
		return *SkeletalMesh;
	}

	FORCEINLINE const FCsFX& GetTrailFX() const
	{
		return *TrailFX;
	}

#pragma endregion ICsData_ProjectileVisual

public:

	FORCEINLINE void SetStaticMesh(UStaticMesh** Value)
	{
		StaticMesh = Value;
	}

	FORCEINLINE void SetSkeletalMesh(USkeletalMesh** Value)
	{
		SkeletalMesh = Value;
	}

	FORCEINLINE void SetTrailFX(FCsFX* Value)
	{
		TrailFX = Value;
	}
};