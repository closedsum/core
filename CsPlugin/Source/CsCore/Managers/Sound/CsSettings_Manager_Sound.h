// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsSettings_Manager_Sound.generated.h"
#pragma once

// FCsSettings_Manager_Sound_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Sound_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsSoundPooled"))
	TSoftClassPtr<UObject> Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsSettings_Manager_Sound_PoolParams() :
		Class(nullptr),
		PoolSize(0),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_PoolParams

// FCsSettings_Manager_Sound
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Sound
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Payload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsSoundType, FCsSettings_Manager_Sound_PoolParams> PoolParams;

	FCsSettings_Manager_Sound() :
		Payload(NAME_None),
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound

// FCsSettings_Manager_Sound_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Sound_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsSoundPooled */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSoundPooled"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSoundPooled"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsSoundPooled"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_Sound_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_UnitTest