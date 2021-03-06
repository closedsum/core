// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "Managers/Trace/CsTypes_Manager_Trace.h"
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"

#include "CsManager_Trace.generated.h"

// Structs
#pragma region

	// TraceRequest
namespace NCsTrace
{
	namespace NRequest
	{
	#define RequestType NCsTrace::NRequest::FRequest

		struct CSCORE_API FResource : public TCsResourceContainer<RequestType>
		{
		};

		struct CSCORE_API FManager : public TCsManager_ResourceValueType_Fixed<RequestType, FResource, 0>
		{
		};

	#undef RequestType
	}
}

	// TraceResponse
namespace NCsTrace
{
	namespace NResponse
	{
	#define ResponseType NCsTrace::NResponse::FResponse

		struct CSCORE_API FResource : public TCsResourceContainer<ResponseType>
		{
		};

		struct CSCORE_API FManager : public TCsManager_ResourceValueType_Fixed<ResponseType, FResource, 0>
		{
		};

	#undef ResponseType
	}
}

#pragma endregion Structs

class ICsGetManagerTrace;

UCLASS()
class CSCORE_API UCsManager_Trace : public UObject
{
	GENERATED_UCLASS_BODY()

#define RequestType NCsTrace::NRequest::FRequest
#define ResponseType NCsTrace::NResponse::FResponse

public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Trace* Get(UObject* InRoot = nullptr);
#else
	static UCsManager_Trace* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr; 
	}
#endif // #if WITH_EDITOR

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

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

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

private:

	UWorld* CurrentWorld;

public:

	void Update(const FCsDeltaTime& DeltaTime);

protected:

	int32 MaxRequestsProcessedPerTick;

#define CountInfoType NCsTrace::NManager::FCountInfo

	/** */
	CountInfoType LifetimeCountInfo;
	/** */
	CountInfoType ThisFrameCountInfo;

#undef CountInfoType

private:

	void IncrementTraceCount(RequestType* Request);

// Request
#pragma region
private:

#define RequestManagerType NCsTrace::NRequest::FManager
	RequestManagerType Manager_Request;
#undef RequestManagerType

public:
	
	RequestType* AllocateRequest();

private:

	void DeallocateRequest(RequestType* Request);

public:

	bool SafeDeallocateRequest(const FString& Context, RequestType* Request, void(*Log)(const FString&) = &FCsLog::Warning);

private:

#define PendingRequestsType NCsTrace::NManager::FPendingRequests
	PendingRequestsType PendingRequests;
#undef PendingRequestsType

	bool ProcessAsyncRequest(RequestType* Request);

	void DrawRequest(const RequestType* Request) const;

#pragma endregion Request

// Response
#pragma region
private:

#define ResponseManagerType NCsTrace::NResponse::FManager
	ResponseManagerType Manager_Response;
#undef ResponseManagerType

public:

	ResponseType* AllocateResponse();

private:

	void DeallocateResponse(ResponseType* Response);

public:

	FTraceDelegate TraceDelegate;
	FOverlapDelegate OverlapDelegate;

private:

	void OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum);
	void OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum);

	void DrawResponse(const RequestType* Request, const ResponseType* Response) const;

#pragma endregion Response

public:

	ResponseType* Trace(RequestType* Request);

protected:

	void LogTransaction(const FString& Context, const ECsTraceTransaction& Transaction, RequestType* Request, ResponseType* Response);

#undef RequestType
#undef ResponseType
};