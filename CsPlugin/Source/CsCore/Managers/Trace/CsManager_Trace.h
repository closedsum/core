// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "Managers/Trace/CsTypes_Manager_Trace.h"
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"

#include "CsManager_Trace.generated.h"

#define CS_POOLED_TRACE_REQUEST_SIZE 255
#define CS_POOLED_TRACE_RESPONSE_SIZE 255

// Structs
#pragma region

	// TraceRequest

struct CSCORE_API FCsResource_TraceRequest : public TCsResourceContainer<FCsTraceRequest>
{
};

struct CSCORE_API FCsManager_TraceRequest : public TCsManager_ResourceValueType_Fixed<FCsTraceRequest, FCsResource_TraceRequest, 0>
{
};

	// TraceResponse

struct CSCORE_API FCsResource_TraceResponse : public TCsResourceContainer<FCsTraceResponse>
{
};

struct CSCORE_API FCsManager_TraceResponse : public TCsManager_ResourceValueType_Fixed<FCsTraceResponse, FCsResource_TraceResponse, 0>
{

};
#pragma endregion Structs

class ICsGetManagerTrace;

UCLASS()
class CSCORE_API UCsManager_Trace : public UObject
{
	GENERATED_UCLASS_BODY()

	// For Clarity
typedef uint8 TCsTraceRequestId;
typedef uint64 TCsTraceHandleId;
typedef uint64 TCsObjectId;

public:

// Singleton
#pragma region
public:

	static UCsManager_Trace* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Trace> ManagerTraceClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerTrace* Get_GetManagerTrace(UObject* InRoot);
	static ICsGetManagerTrace* GetSafe_GetManagerTrace(UObject* Object);

	static UCsManager_Trace* GetSafe(UObject* Object);

public:

	static UCsManager_Trace* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Trace* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	virtual void OnTick(const float &DeltaSeconds);

	int32 RequestsProcessedPerTick;

	/** */
	FCsManagerTraceCountInfo LifetimeCountInfo;
	/** */
	FCsManagerTraceCountInfo ThisFrameCountInfo;

private:

	void IncrementTraceCount(FCsTraceRequest* Request);

// Request
#pragma region
private:

	FCsManager_TraceRequest Manager_Request;

public:
	
	FCsTraceRequest* AllocateRequest();

private:

	void DeallocateRequest(FCsTraceRequest* Request);

	FCsManagerTracePendingRequests PendingRequests;

	bool ProcessRequest(FCsTraceRequest* Request);

#pragma endregion Request

// Response
#pragma region
private:

	FCsManager_TraceResponse Manager_Response;

public:

	FCsTraceResponse* AllocateResponse();

private:

	void DeallocateResponse(FCsTraceResponse* Response);

public:

	FTraceDelegate TraceDelegate;
	FOverlapDelegate OverlapDelegate;

private:

	void OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum);
	void OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum);

#pragma endregion Response

public:

	FCsTraceResponse* Trace(FCsTraceRequest* Request);

	virtual void LogTransaction(const FString& FunctionName, const ECsTraceTransaction& Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response);
};