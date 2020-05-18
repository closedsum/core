// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/CsTdTypes_Creep.h"
#include "CsTdSettings_Manager_Creep.generated.h"
#pragma once

// FCsTdSettings_Manager_Creep_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSTD_API FCsTdSettings_Manager_Creep_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsTdCreep"))
	TSoftClassPtr<AActor> Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsTdSettings_Manager_Creep_PoolParams() :
		Class(nullptr),
		PoolSize(0),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsTdSettings_Manager_Creep_PoolParams

// FCsTdSettings_Manager_Creep
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSTD_API FCsTdSettings_Manager_Creep
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsTdCreep, FCsTdSettings_Manager_Creep_PoolParams> PoolParams;

	FCsTdSettings_Manager_Creep() :
		PoolParams()
	{
	}
};

#pragma endregion FCsTdSettings_Manager_Creep

// FCsTdSettings_Manager_Creep_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSTD_API FCsTdSettings_UnitTestPlan_Manager_Creep
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsTdCreep. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsTdCreep"))
	TSoftClassPtr<AActor> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsTdCreep"))
	TSoftClassPtr<AActor> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsTdCreep"))
	TSoftClassPtr<AActor> ClassC;

	FCsTdSettings_UnitTestPlan_Manager_Creep() :
		Map(),
		ClassA(FSoftObjectPath("/Script/CsTd.CsTdCreep_UnitTest_A")),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsTdSettings_Manager_Creep