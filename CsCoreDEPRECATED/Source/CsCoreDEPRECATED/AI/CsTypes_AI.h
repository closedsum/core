// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"

#include "CsTypes_AI.generated.h"
#pragma once

// AIType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsAIType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAIType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAIType)

struct CSCOREDEPRECATED_API EMCsAIType : public TCsEnumStructMap<FECsAIType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsAIType, FECsAIType, uint8)
};

#pragma endregion AIType

// AIState
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsAIState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAIState)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAIState)

struct CSCOREDEPRECATED_API EMCsAIState : public TCsEnumStructMap<FECsAIState, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsAIState, FECsAIState, uint8)
};

#pragma endregion AIState

// AISetup
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsAISetup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAISetup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAISetup)

struct CSCOREDEPRECATED_API EMCsAISetup : public TCsEnumStructMap<FECsAISetup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsAISetup, FECsAISetup, uint8)
};

#pragma endregion AISetup

// FCsAIPawnPayload
#pragma region

struct CSCOREDEPRECATED_API FCsAIPawnPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	bool bLocation;

	FVector Location;

	bool bRotation;

	FRotator Rotation;

	FCsAIPawnPayload()
	{
		Reset();
	}
	~FCsAIPawnPayload() {}

// ICsPooledObjectPayload
#pragma region
public:

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

		bLocation = false;
		Location = FVector::ZeroVector;
		bRotation = false;
		Rotation = FRotator::ZeroRotator;
	}

#pragma endregion ICsPooledObjectPayload
};

#pragma endregion FCsAIPawnPayload