// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "CsSettings_Manager_StaticMeshActor.generated.h"
#pragma once

// FCsSettings_Manager_StaticMeshActor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_StaticMeshActor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsStaticMeshActor"))
	FECsStaticMeshActorClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_StaticMeshActor_PoolParams() :
		Class(),
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
struct CSCORE_API FCsSettings_Manager_StaticMeshActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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
struct CSCORE_API FCsSettings_Manager_StaticMeshActor_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsStaticMeshActor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsStaticMeshActor"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsStaticMeshActor"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsStaticMeshActor"))
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