// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"
#include "CsSettings_Manager_FX_Actor.generated.h"
#pragma once

// FCsSettings_Manager_FX_Actor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_Actor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsFXPooledActor"))
	TSoftClassPtr<UObject> Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsSettings_Manager_FX_Actor_PoolParams() :
		Class(nullptr),
		PoolSize(0),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_Actor_PoolParams

// FCsSettings_Manager_FX_Actor
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_Actor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Payload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsFX, FCsSettings_Manager_FX_Actor_PoolParams> PoolParams;

	FCsSettings_Manager_FX_Actor() :
		Payload(NAME_None),
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_Actor

// FCsSettings_Manager_FX_Actor_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_Actor_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsFXPooledActor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsFXPooledActor"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsFXPooledActor"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsFXPooledActor"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_FX_Actor_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_Actor_UnitTest