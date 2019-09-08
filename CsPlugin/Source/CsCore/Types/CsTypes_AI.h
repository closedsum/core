// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Pool.h"

#include "CsTypes_AI.generated.h"
#pragma once

// AI
#pragma region

	// AIType

USTRUCT(BlueprintType)
struct CSCORE_API FECsAIType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAIType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAIType)

struct CSCORE_API EMCsAIType : public TCsEnumStructMap<FECsAIType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsAIType)
};

	// AIState

USTRUCT(BlueprintType)
struct CSCORE_API FECsAIState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAIState)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAIState)

struct CSCORE_API EMCsAIState : public TCsEnumStructMap<FECsAIState, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsAIState)
};

	// AISetup

USTRUCT(BlueprintType)
struct CSCORE_API FECsAISetup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAISetup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAISetup)

struct CSCORE_API EMCsAISetup : public TCsEnumStructMap<FECsAISetup, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsAISetup)
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAIPawnPayload : public FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	bool bLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	FVector Location;
	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	bool bRotation;
	UPROPERTY(BlueprintReadWrite, Category = "Payload")
	FRotator Rotation;

	FCsAIPawnPayload()
	{
		Reset();
	}
	~FCsAIPawnPayload() {}

	FORCEINLINE virtual void Reset() override
	{
		Super::Reset();

		bLocation = false;
		Location = FVector::ZeroVector;
		bRotation = false;
		Rotation = FRotator::ZeroRotator;
	}
};

#pragma endregion AI