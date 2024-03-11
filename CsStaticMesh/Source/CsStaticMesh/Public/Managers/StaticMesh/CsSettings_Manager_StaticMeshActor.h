// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "CsSettings_Manager_StaticMeshActor.generated.h"

// FCsSettings_Manager_StaticMeshActor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsSettings_Manager_StaticMeshActor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (MustImplement = "/Script/CsCore.CsStaticMeshActor"))
	TSoftClassPtr<UObject> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_StaticMeshActor_PoolParams() :
		Class(nullptr),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_StaticMeshActor_PoolParams

// FCsSettings_Manager_StaticMeshActor
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsSettings_Manager_StaticMeshActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh")
	TMap<FECsStaticMeshActor, FCsSettings_Manager_StaticMeshActor_PoolParams> PoolParams;

	FCsSettings_Manager_StaticMeshActor() :
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_StaticMeshActor

// FCsSettings_Manager_StaticMeshActor_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsSettings_Manager_StaticMeshActor_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsStaticMeshActor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (MustImplement = "/Script/CsCore.CsStaticMeshActor"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (MustImplement = "/Script/CsCore.CsStaticMeshActor"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh", meta = (MustImplement = "/Script/CsCore.CsStaticMeshActor"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_StaticMeshActor_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_StaticMeshActor_UnitTest