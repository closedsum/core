// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

public:
	FECsAIType() {}
	FECsAIType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsAIType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsAIType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsAIType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsAIType : public TCsEnumStructMap<FECsAIType, uint8>
{
protected:
	EMCsAIType() {}
	EMCsAIType(const EMCsAIType &) = delete;
	EMCsAIType(EMCsAIType &&) = delete;
public:
	~EMCsAIType() {}
private:
	static EMCsAIType* Instance;

public:
	static EMCsAIType& Get();
};

	// AIState

USTRUCT(BlueprintType)
struct CSCORE_API FECsAIState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsAIState() {}
	FECsAIState(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsAIState(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsAIState() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsAIState& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsAIState : public TCsEnumStructMap<FECsAIState, uint8>
{
protected:
	EMCsAIState() {}
	EMCsAIState(const EMCsAIState &) = delete;
	EMCsAIState(EMCsAIState &&) = delete;
public:
	~EMCsAIState() {}
private:
	static EMCsAIState* Instance;

public:
	static EMCsAIState& Get();
};

namespace ECsAISetup
{
	enum Type : uint8;
}

	// AISetup

USTRUCT(BlueprintType)
struct CSCORE_API FECsAISetup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsAISetup() {}
	FECsAISetup(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsAISetup(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsAISetup() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsAISetup& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsAISetup : public TCsEnumStructMap<FECsAISetup, uint8>
{
protected:
	EMCsAISetup() {}
	EMCsAISetup(const EMCsAISetup &) = delete;
	EMCsAISetup(EMCsAISetup &&) = delete;
public:
	~EMCsAISetup() {}
private:
	static EMCsAISetup* Instance;

public:
	static EMCsAISetup& Get();
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
		FCsPooledObjectPayload::Reset();

		bLocation = false;
		Location = FVector::ZeroVector;
		bRotation = false;
		Rotation = FRotator::ZeroRotator;
	}
};

#pragma endregion AI