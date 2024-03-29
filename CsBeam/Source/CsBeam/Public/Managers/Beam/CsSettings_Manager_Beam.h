// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Beam.h"
#include "Payload/CsTypes_Payload_Beam.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsSettings_Manager_Beam.generated.h"

// FCsSettings_Manager_Beam_TypeArray
#pragma region

USTRUCT(BlueprintType)
struct CSBEAM_API FCsSettings_Manager_Beam_TypeArray
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	TArray<FECsBeam> Types;

	FCsSettings_Manager_Beam_TypeArray() :
		Types()
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_TypeArray

// FCsSettings_Manager_Beam_PoolParams
#pragma region

/**
* Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Beam type.
* These parameters are used when initially creating the pool.
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsSettings_Manager_Beam_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The class of the pooled Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	FECsBeamClass Class;
	/** The maximum size of the pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;
	/** The maximum payload size. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_Beam_PoolParams() :
		Class(),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Beam_PoolParams

// FCsSettings_Manager_Beam
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsSettings_Manager_Beam
{
	GENERATED_USTRUCT_BODY()

public:

	/** Mapping for sharing a pool of beams between many Beam types. This is useful
		when multiple Beam types share the same Beam Class. In this case, it is not
		necessary to create separate pool for each Beam type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	TMap<FECsBeam, FECsBeam> TypeMap;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	TSet<FECsBeamPayload> PayloadTypes;

	/** Mapping between Update Groups, the "tick" / update group, and Sound types. This
		is important to indicate when a particular Sound type WILL or will NOT get "ticked" or updated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	TMap<FECsUpdateGroup, FCsSettings_Manager_Beam_TypeArray> TypesByUpdateGroupMap;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Beam type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam")
	TMap<FECsBeam, FCsSettings_Manager_Beam_PoolParams> PoolParams;

	FCsSettings_Manager_Beam() :
		TypeMap(),
		PayloadTypes(),
		TypesByUpdateGroupMap(),
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_Beam

// FCsSettings_Manager_Beam_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsSettings_Manager_Beam_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsBeam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (MustImplement = "/Script.CsBeam.CsBeam"))
	TSoftClassPtr<AActor> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (MustImplement = "/Script.CsBeam.CsBeam"))
	TSoftClassPtr<AActor> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Settings|Manager|Beam", meta = (MustImplement = "/Script.CsBeam.CsBeam"))
	TSoftClassPtr<AActor> ClassC;

	FCsSettings_Manager_Beam_UnitTest() :
		Map(),
		ClassA(FSoftObjectPath("/Script/CsBeam.CsBeam_UnitTest_A")),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_Beam_UnitTest