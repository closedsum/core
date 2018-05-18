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

UENUM(BlueprintType)
namespace ECsProcessMonitorOutputEventPurpose
{
	enum Type
	{
		FireOnce								UMETA(DisplayName = "FireOnce"),
		Loop									UMETA(DisplayName = "Loop"),
		ECsProcessMonitorOutputEventPurpose_MAX	UMETA(Hidden),
	};
}

#define ECS_PROCESS_MONITOR_OUTPUT_EVENT_PURPOSE (uint8)ECsProcessMonitorOutputEventPurpose::ECsProcessMonitorOutputEventPurpose_MAX
typedef ECsProcessMonitorOutputEventPurpose::Type TCsProcessMonitorOutputEventPurpose;

namespace ECsProcessMonitorOutputEventPurpose
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString FireOnce = TCsString(TEXT("FireOnce"), TEXT("fireonce"));
		const TCsString Loop = TCsString(TEXT("Loop"), TEXT("Loop"));
	}

	namespace Ref
	{
		const Type FireOnce = Type::FireOnce;
		const Type Loop = Type::Loop;
		const Type ECsProcessMonitorOutputEventPurpose_MAX = Type::ECsProcessMonitorOutputEventPurpose_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::FireOnce) { return Str::FireOnce.Value; }
		if (EType == Type::Loop) { return Str::Loop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::FireOnce) { return Ref::FireOnce; }
		if (String == Str::Loop) { return Ref::Loop; }
		return Ref::ECsProcessMonitorOutputEventPurpose_MAX;
	}
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProcessMonitorOutputEvent_CompletedEvent, const FString&, Name);

USTRUCT(BlueprintType)
struct FCsProcessMonitorOutputEvent
{
	GENERATED_USTRUCT_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FCompletedEvent, const FString&);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	TEnumAsByte<ECsProcessMonitorOutputEventPurpose::Type> Purpose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool Completed;

	FCompletedEvent Event;
	UPROPERTY(BlueprintAssignable, Category = "Process")
	FBindableDynEvent_CsProcessMonitorOutputEvent_CompletedEvent ScriptEvent;

public:
	FCsProcessMonitorOutputEvent() {}
	~FCsProcessMonitorOutputEvent() {}
};

USTRUCT(BlueprintType)
struct FCsProcessPayload : public FCgPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

public:
	FCsProcessPayload() {}
	~FCsProcessPayload() {}
};

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