// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"

#include "CsSettings_Manager_FX.generated.h"

// FCsSettings_Manager_FX_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (MustImplement = "/Script.CsCore.CsFXActorPooled"))
	TSoftClassPtr<UObject> Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_FX_PoolParams() :
		Class(nullptr),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_PoolParams


// FCsSettings_Manager_FX_Parameters
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_Parameters
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "CsCore|Managers|FX")
	int32 PoolSizes[(uint8)ECsFXParameterValue::ECsFXParameterValue_MAX];

	FCsSettings_Manager_FX_Parameters()
	{
		for (const ECsFXParameterValue& Value : EMCsFXParameterValue::Get())
		{
			PoolSizes[(int32)Value] = 4;
		}
	}
};

#pragma endregion FCsSettings_Manager_FX_Parameters

// FCsSettings_Manager_FX
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX")
	TMap<FECsFX, FCsSettings_Manager_FX_PoolParams> PoolParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX")
	FCsSettings_Manager_FX_Parameters Parameters;

	FCsSettings_Manager_FX() :
		PoolParams(),
		Parameters()
	{
	}

	static const FCsSettings_Manager_FX& GetChecked(const FString& Context);
};

#pragma endregion FCsSettings_Manager_FX

// FCsSettings_Manager_FX_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_FX_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (AllowedClasses = "/Script/CsCore.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsFXActorPooled */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (MustImplement = "/Script.CsCore.CsFXActorPooled"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (MustImplement = "/Script.CsCore.CsFXActorPooled"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|FX", meta = (MustImplement = "/Script.CsCore.CsFXActorPooled"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_FX_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_UnitTest