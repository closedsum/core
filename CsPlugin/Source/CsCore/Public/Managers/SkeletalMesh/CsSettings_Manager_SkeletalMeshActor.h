// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsSettings_Manager_SkeletalMeshActor.generated.h"
#pragma once

// FCsSettings_Manager_SkeletalMeshActor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_SkeletalMeshActor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSkeletalMeshActor"))
	TSoftClassPtr<UObject> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_SkeletalMeshActor_PoolParams() :
		Class(nullptr),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_SkeletalMeshActor_PoolParams

// FCsSettings_Manager_SkeletalMeshActor
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_SkeletalMeshActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsSkeletalMeshActor, FCsSettings_Manager_SkeletalMeshActor_PoolParams> PoolParams;

	FCsSettings_Manager_SkeletalMeshActor() :
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_SkeletalMeshActor

// FCsSettings_Manager_SkeletalMeshActor_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_SkeletalMeshActor_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsSkeletalMeshActor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSkeletalMeshActor"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSkeletalMeshActor"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSkeletalMeshActor"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_SkeletalMeshActor_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_SkeletalMeshActor_UnitTest