// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Types
#include "Managers/Trace/CsTypes_Trace.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsManager_Trace.generated.h"

// Enums
#pragma region

	// TraceTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsTraceTransaction : uint8
{
	Add						UMETA(DisplayName = "Add"),
	Complete				UMETA(DisplayName = "Complete"),
	ECsTraceTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceTransaction : public TCsEnumMap<ECsTraceTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceTransaction, ECsTraceTransaction)
};

namespace NCsTraceTransaction
{
	typedef ECsTraceTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsTraceTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Add;
		extern CSCORE_API const TCsString Complete;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Complete) { return Str::Complete.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#define ECS_TRACE_TRANSACTION_MAX NCsTraceTransaction::MAX

#pragma endregion TraceTransaction

#pragma endregion Enums

#define CS_POOLED_TRACE_REQUEST_SIZE 255
#define CS_POOLED_TRACE_RESPONSE_SIZE 255

UCLASS()
class CSCORE_API ACsManager_Trace : public AActor
{
	GENERATED_UCLASS_BODY()

	// For Clarity
typedef uint8 TCsTraceRequestId;
typedef uint64 TCsTraceHandleId;
typedef uint64 TCsObjectId;

public:

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;

	static ACsManager_Trace* Get(UWorld* InWorld);

	virtual void OnTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	int32 RequestsProcessedPerTick;

	uint64 TraceCountLifetime;

	TMap<uint64, uint64> TraceCountLifetimeByObjectId;
	uint64 TraceCountLifetimeByType[ECsTraceType::ECsTraceType_MAX];
	uint64 TraceCountLifetimeByMethod[ECsTraceMethod::ECsTraceMethod_MAX];
	uint64 TraceCountLifetimeByQuery[ECsTraceQuery::ECsTraceQuery_MAX];

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	int32 TraceCountThisFrame;

	TMap<uint64, uint16> TraceCountThisFrameByObjectId;
	uint16 TraceCountThisFrameByType[ECsTraceType::ECsTraceType_MAX];
	uint16 TraceCountThisFrameByMethod[ECsTraceMethod::ECsTraceMethod_MAX];
	uint16 TraceCountThisFrameByQuery[ECsTraceQuery::ECsTraceQuery_MAX];

private:

	void IncrementTraceCount(FCsTraceRequest* Request);

// Request
#pragma region
private:

	FCsTraceRequest Requests[CS_POOLED_TRACE_REQUEST_SIZE];

	uint8 RequestIndex;

public:
	
	FCsTraceRequest* AllocateRequest();

	TLinkedList<FCsTraceRequest*>* PendingRequestHead;
	TLinkedList<FCsTraceRequest*>* PendingRequestTail;

	TMap<TCsTraceRequestId, FCsTraceRequest*> PendingRequests;
	TMap<TCsTraceHandleId, FCsTraceRequest*> PendingRequestsByTraceId;
	TMap<TCsObjectId, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByObjectId;
	TMap<ECsTraceType, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByType;
	TMap<ECsTraceMethod, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByMethod;
	TMap<ECsTraceQuery, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByQuery;

private:

	void AddPendingRequest(FCsTraceRequest* Request);
	void ReplacePendingRequest(FCsTraceRequest* PendingRequest, FCsTraceRequest* Request);
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

	virtual void LogTransaction(const FString& FunctionName, const ECsTraceTransaction& Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response);
};