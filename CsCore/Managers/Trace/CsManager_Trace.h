// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Trace.h"
#include "CsManager_Trace.generated.h"

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsTraceTransaction
{
	enum Type
	{
		Add						UMETA(DisplayName = "Add"),
		Complete				UMETA(DisplayName = "Complete"),
		ECsTraceTransaction_MAX	UMETA(Hidden),
	};
}

namespace ECsTraceTransaction
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Add = TCsString(TEXT("Add"), TEXT("add"), TEXT("Adding"));
		const TCsString Complete = TCsString(TEXT("Complete"), TEXT("complete"), TEXT("Completing"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Value; }
		if (EType == Type::Complete) { return Str::Complete.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Complete) { return Str::Complete.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Add) { return Type::Add; }
		if (String == Str::Complete) { return Type::Complete; }
		return Type::ECsTraceTransaction_MAX;
	}
}

#define ECS_TRACE_TRANSACTION_MAX (uint8)ECsTraceTransaction::ECsTraceTransaction_MAX
typedef ECsTraceTransaction::Type TCsTraceTransaction;

#pragma endregion Enums

#define CS_POOLED_TRACE_REQUEST_SIZE 255
#define CS_POOLED_TRACE_RESPONSE_SIZE 255

// For Clarity
typedef uint64 TCsTraceHandleId;
typedef uint64 TCsObjectId;

UCLASS()
class CSCORE_API ACsManager_Trace : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;

	static ACsManager_Trace* Get(UWorld* InWorld);

	virtual void OnTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	int32 RequestsProcessedPerTick;

	uint64 TraceCountLifetime;

	TMap<uint64, uint64> TraceCountLifetimeById;
	uint64 TraceCountLifetimeByType[ECS_TRACE_TYPE_MAX];
	uint64 TraceCountLifetimeByMethod[ECS_TRACE_METHOD_MAX];
	uint64 TraceCountLifetimeByQuery[ECS_TRACE_QUERY_MAX];

	uint16 TraceCountThisFrame;

	TMap<uint64, uint16> TraceCountThisFrameById;
	uint16 TraceCountThisFrameByType[ECS_TRACE_TYPE_MAX];
	uint16 TraceCountThisFrameByMethod[ECS_TRACE_METHOD_MAX];
	uint16 TraceCountThisFrameByQuery[ECS_TRACE_QUERY_MAX];

private:

	void IncrementTraceCount(FCsTraceRequest* Request);

// Request
#pragma region
private:

	FCsTraceRequest Requests[CS_POOLED_TRACE_REQUEST_SIZE];

	uint8 RequestIndex;

public:

	FCsTraceRequest* AllocateRequest();

	TMap<TCsTraceHandleId, FCsTraceRequest*> PendingRequests;
	TMap<TCsObjectId, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsById;
	TMap<TCsTraceType, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByType;
	TMap<TCsTraceMethod, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByMethod;
	TMap<TCsTraceQuery, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByQuery;

private:

	void AddPendingRequest(FCsTraceRequest* Request);
	void RemovePendingRequest(FCsTraceRequest* Request);
	bool ProcessRequest(FCsTraceRequest* Request);

#pragma endregion Request

// Response
#pragma region
private:

	FCsTraceResponse Responses[CS_POOLED_TRACE_RESPONSE_SIZE];

	uint8 ResponseIndex;

public:

	FCsTraceResponse * AllocateResponse();

	FTraceDelegate TraceDelegate;
	FOverlapDelegate OverlapDelegate;

	void OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum);
	void OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum);

#pragma endregion Response

public:

	FCsTraceResponse* Trace(FCsTraceRequest* Request);

	virtual void LogTransaction(const FString &FunctionName, const TCsTraceTransaction &Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response);
};