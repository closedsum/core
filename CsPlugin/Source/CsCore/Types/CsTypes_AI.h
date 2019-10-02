// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"

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

struct CSCORE_API FCsAIPawnPayload : public ICsPooledObjectPayload
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

#pragma endregion AI