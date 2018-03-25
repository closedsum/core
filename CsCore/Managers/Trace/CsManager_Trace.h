// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Trace.h"
#include "CsManager_Trace.generated.h"

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
};