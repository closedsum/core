// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsPooledObject.h"
#include "Types/CsTypes_Pool.h"
#include "CsProcess.generated.h"

USTRUCT(BlueprintType)
struct FECsProcess : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsProcess(){}
	FECsProcess(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsProcess() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsProcess& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsProcess));
}

struct EMCsProcess : public TCsEnumMap<FECsProcess, uint8>
{
protected:
	EMCsProcess(){}
	EMCsProcess(const EMCsProcess &) = delete;
	EMCsProcess(EMCsProcess &&) = delete;
public:
	~EMCsProcess(){}

	static EMCsProcess& Get()
	{
		static EMCsProcess Instance;
		return Instance;
	}
};

USTRUCT(BlueprintType)
struct FCsProcessPayload : public FCgPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

public:
	FCsProcessPayload() {}
	~FCsProcessPayload() {}
};

/*
namespace ECsProcessTest
{
	extern const FCsProcess Default;
	extern const FCsProcess MAX;
}
*/

USTRUCT(BlueprintType)
struct FCsProcessCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	FCsProcessCache()
	{
		Reset();
	}

	~FCsProcessCache() {}

	void Init(const uint16& InActiveIndex, FCsProcessPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		//Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();
	}
};

UCLASS()
class CSCORE_API UCsProcess : public UCsPooledObject
{
	GENERATED_UCLASS_BODY()

public:

	FCsProcessCache Cache;

	void Init(const int32 &Index, const FECsProcess &Type);
	void OnCreatePool();
	void Allocate(const int32 &Index, FCsProcessPayload* Payload);
	void DeAllocate();
};