// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsManager_Trace.h"
#include "CsCore.h"

// CVars
#include "Managers/Trace/CsCVars_Manager_Trace.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"
// UniqueObject
#include "UniqueObject/CsUniqueObject.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Trace/CsGetManagerTrace.h"
#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsManagerTrace
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, ProcessAsyncRequest);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, OnTraceResponse);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, OnOverlapResponse);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Trace, Trace);
		}
	}
}

#pragma endregion Cache

// ScopedTimer
#pragma region

namespace NCsManagerTrace
{
	namespace NScopedTimer
	{
		FCsScopedTimerHandle Update;
		FCsScopedTimerHandle ProcessAsyncRequest;
		FCsScopedTimerHandle Trace;

		void Setup()
		{
			using namespace NCached;

			// Update
			{
				const FString& ScopeName		   = Str::Update;
				const FECsScopedGroup& ScopedGroup = NCsScopedGroup::ManagerTrace;
				const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogManagerTraceScopedTimerUpdate;

				Update = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
			}
			// ProcessAsyncRequest
			{
				const FString& ScopeName		   = Str::ProcessAsyncRequest;
				const FECsScopedGroup& ScopedGroup = NCsScopedGroup::ManagerTrace;
				const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogManagerTraceScopedTimerProcessAsyncRequest;

				ProcessAsyncRequest = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
			}
			// Trace
			{
				const FString& ScopeName		   = Str::Trace;
				const FECsScopedGroup& ScopedGroup = NCsScopedGroup::ManagerTrace;
				const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogManagerTraceScopedTimerTrace;

				Trace = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
			}
		}

		void Clear()
		{
			FCsManager_ScopedTimer::Get().SilentClearHandle(Update);
			FCsManager_ScopedTimer::Get().SilentClearHandle(ProcessAsyncRequest);
			FCsManager_ScopedTimer::Get().SilentClearHandle(Trace);
		}
	}
}

#pragma endregion ScopedTimer

// static initializations
UCsManager_Trace* UCsManager_Trace::s_Instance;
bool UCsManager_Trace::s_bShutdown = false;

UCsManager_Trace::UCsManager_Trace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Trace* UCsManager_Trace::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerTrace(InRoot)->GetManager_Trace();
}
#endif // #if WITH_EDITOR


#if WITH_EDITOR
/*static*/ bool UCsManager_Trace::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerTrace(InRoot)->GetManager_Trace() != nullptr;
}
#endif // #if WITH_EDITORs

/*static*/ void UCsManager_Trace::Init(UObject* InRoot, TSubclassOf<UCsManager_Trace> ManagerTraceClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerTrace* GetManagerTrace = Get_GetManagerTrace(InRoot);

	UCsManager_Trace* Manager_Trace = GetManagerTrace->GetManager_Trace();

	if (!Manager_Trace)
	{
		Manager_Trace = NewObject<UCsManager_Trace>(InOuter ? InOuter : InRoot, ManagerTraceClass, TEXT("Manager_Trace_Singleton"), RF_Transient | RF_Public);

		GetManagerTrace->SetManager_Trace(Manager_Trace);

		Manager_Trace->SetMyRoot(InRoot);
		Manager_Trace->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Trace>(GetTransientPackage(), ManagerTraceClass, TEXT("Manager_Trace_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Trace::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerTrace* GetManagerTrace = Get_GetManagerTrace(InRoot);
	UCsManager_Trace* Manager_Trace	    = GetManagerTrace->GetManager_Trace();
	Manager_Trace->CleanUp();

	GetManagerTrace->SetManager_Trace(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Trace::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerTrace(InRoot)->GetManager_Trace() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerTrace* UCsManager_Trace::Get_GetManagerTrace(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Trace::Get_GetManagerTrace: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Trace::Get_GetManagerTrace: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Trace::Get_GetManagerTrace: Manager_Singleton is NULL."));

	ICsGetManagerTrace* GetManagerTrace = Cast<ICsGetManagerTrace>(Manager_Singleton);

	checkf(GetManagerTrace, TEXT("UCsManager_Trace::Get_GetManagerTrace: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerTrace."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerTrace;
}

/*static*/ ICsGetManagerTrace* UCsManager_Trace::GetSafe_GetManagerTrace(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::GetSafe_GetManagerTrace: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::GetSafe_GetManagerTrace: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::GetSafe_GetManagerTrace: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerTrace>(Manager_Singleton);
}

/*static*/ UCsManager_Trace* UCsManager_Trace::GetSafe(UObject* Object)
{
	if (ICsGetManagerTrace* GetManagerTrace = GetSafe_GetManagerTrace(Object))
		return GetManagerTrace->GetManager_Trace();
	return nullptr;
}

/*static*/ UCsManager_Trace* UCsManager_Trace::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	using namespace NCsManagerTrace::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

	if (UObject* ContextRoot = TraceManagerLibrary::GetSafeContextRoot(Context, WorldContextObject))
	{
		// Game State
		if (UCsManager_Trace* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("%s: Failed to Manager Trace of type UCsManager_Trace from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Trace::Initialize()
{
	using namespace NCsManagerTrace::NCached;

	CurrentWorld = MyRoot->GetWorld();

	checkf(CurrentWorld, TEXT("UCsManager_Trace::Initialize: Failed to get a World from MyRoot: %s."), *(MyRoot->GetName()));

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	checkf(Settings, TEXT("UCsManager_Trace::Initialize: Failed to find Settings of type: UCsDeveloperSettings."));

	MaxRequestsProcessedPerTick = Settings->Manager_Trace.MaxRequestsProcessedPerTick;

	checkf(MaxRequestsProcessedPerTick >= 4, TEXT("UCsManager_Trace::Initialize: MaxRequestsProcessedPerTick is NOT >= 4."));

	TraceDelegate.BindUObject(this, &UCsManager_Trace::OnTraceResponse);
	OverlapDelegate.BindUObject(this, &UCsManager_Trace::OnOverlapResponse);

	// Set Pool Size for Requests and Responses
	const int32& PoolSize = Settings->Manager_Trace.PoolSize;
	
	checkf(PoolSize >= 4, TEXT("UCsManager_Trace::Initialize: PoolSize is NOT >= 4."));

	// Request
	{
		typedef NCsTrace::NRequest::FResource RequestContainerType;
		typedef NCsTrace::NRequest::FRequest RequestType;

		Manager_Request.CreatePool(PoolSize);

		const TArray<RequestContainerType*>& Pool = Manager_Request.GetPool();

		for (RequestContainerType* Container : Pool)
		{
			RequestType* R	   = Container->Get();
			const int32& Index = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Response
	{
		Manager_Response.CreatePool(PoolSize);

		typedef NCsTrace::NResponse::FResource ResponseContainerType;
		typedef NCsTrace::NResponse::FResponse ResponseType;

		const TArray<ResponseContainerType*>& Pool = Manager_Response.GetPool();

		for (ResponseContainerType* Container : Pool)
		{
			ResponseType* R     = Container->Get();
			const int32& Index  = Container->GetIndex();
			R->SetIndex(Index);
		}
	}

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	NCsManagerTrace::NScopedTimer::Setup();
#endif // #if !UE_BUILD_SHIPPING
	bInitialized = true;
}

/*static*/ bool UCsManager_Trace::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Trace::CleanUp()
{
	Manager_Request.Shutdown();
	Manager_Response.Shutdown();

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	NCsManagerTrace::NScopedTimer::Clear();
#endif // #if !UE_BUILD_SHIPPING

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Trace::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Trace::Update(const FCsDeltaTime& DeltaTime)
{
	CS_SCOPED_TIMER_NAMESPACE_2(NCsManagerTrace, NScopedTimer, Update);

	using namespace NCsManagerTrace::NCached;

	const FString& Context = Str::Update;

	// Reset TraceCountThisFrame
	ThisFrameCountInfo.Reset();

	// Process Requests
	{
		const int32 ProcessCountMax = FMath::Max(0, MaxRequestsProcessedPerTick - (int32)ThisFrameCountInfo.TotalCount);
		const int32 Count			= FMath::Min(Manager_Request.GetAllocatedSize(), ProcessCountMax);

		int32 I = 0;

		typedef NCsTrace::NRequest::FResource RequestContainerType;
		typedef NCsTrace::NRequest::FRequest RequestType;

		TCsDoubleLinkedList<RequestContainerType*>* Current = Manager_Request.GetAllocatedHead();
		TCsDoubleLinkedList<RequestContainerType*>* Next	= Current;

		while (Next)
		{
			Current							= Next;
			RequestContainerType* Container = **Current;
			Next							= Current->GetNextLink();

			RequestType* Request = Container->Get();

			check(Request->IsValidChecked(Context));

			// If Processing, SKIP
			if (Request->bProcessing)
				continue;
			// If COMPLETED, Remove
			if (Request->bCompleted)
			{
				CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Complete, Request, Request->Response));

				typedef NCsTrace::NResponse::FResponse ResponseType;

				if (ResponseType* Response = Request->Response)
				{
					CS_NON_SHIPPING_EXPR(DrawResponse(Request, Response));
					Request->OnResponse_Event.Broadcast(Response);
				}
				PendingRequests.Remove(Request);
				DeallocateRequest(Request);
				continue;
			}
			// Check to remove STALE Request
			if (Request->HasExpired())
			{
				CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, Request->Response));

				PendingRequests.Remove(Request);
				DeallocateRequest(Request);
				continue;
			}
			// PROCESS Request
			if (I < Count)
			{
				const bool Success = ProcessAsyncRequest(Request);

				if (Success)
					IncrementTraceCount(Request);
				else
					continue;
			}
			Request->Update(DeltaTime);
			++I;
		}
	}
	// Process Responses
	{
		typedef NCsTrace::NResponse::FResource ResponseContainerType;
		typedef NCsTrace::NResponse::FResponse ResponseType;

		TCsDoubleLinkedList<ResponseContainerType*>* Current = Manager_Response.GetAllocatedHead();
		TCsDoubleLinkedList<ResponseContainerType*>* Next	= Current;

		while (Next)
		{
			Current							 = Next;
			ResponseContainerType* Container = **Current;
			Next							 = Current->GetNextLink();

			ResponseType* Response = Container->Get();

			// Check to deallocate Response
			if (Response->ShouldDeallocate())
			{
				DeallocateResponse(Response);
			}
		}
	}
}

#define RequestType NCsTrace::NRequest::FRequest
void UCsManager_Trace::IncrementTraceCount(RequestType* Request)
{
#undef RequestType

	// Lifetime
	LifetimeCountInfo.Increment(Request);
	// Frame
	ThisFrameCountInfo.Increment(Request);
}

// Request
#pragma region

#define RequestType NCsTrace::NRequest::FRequest

RequestType* UCsManager_Trace::AllocateRequest()
{
	typedef NCsTrace::NRequest::FResource RequestResourceType;

	RequestResourceType* Container = Manager_Request.Allocate();

	return Container->Get();
}

void UCsManager_Trace::DeallocateRequest(RequestType* Request)
{
	typedef NCsTrace::NResponse::FResponse ResponseType;

	if (ResponseType* Response = Request->Response)
		DeallocateResponse(Response);

	Request->Reset();
	Manager_Request.DeallocateAt(Request->GetIndex());
}

bool UCsManager_Trace::SafeDeallocateRequest(const FString& Context, RequestType* Request, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	CS_IS_PTR_NULL(Request)

	if (Request->GetIndex() < 0)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Request->GetIndex(): %s id NOT Valid."), *Context, Request->GetIndex()));
		return false;
	}

	if (Request->GetIndex() >= Manager_Request.GetPoolSize())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Request is NOT apart of Manager_Request's pool."), *Context));
		return false;
	}

	if (!Manager_Request.Contains(Request))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Request is NOT apart of Manager_Request's pool."), *Context));
		return false;
	}

	DeallocateRequest(Request);
	return true;
}

bool UCsManager_Trace::ProcessAsyncRequest(RequestType* Request)
{
	CS_SCOPED_TIMER_NAMESPACE_2(NCsManagerTrace, NScopedTimer, ProcessAsyncRequest);

	using namespace NCsManagerTrace::NCached;

	const FString& Context = Str::ProcessAsyncRequest;

	CS_IS_PTR_NULL_CHECKED(Request)

	checkf(Request->IsValid(), TEXT("%s: Request is NOT Valid."), *Context);

	CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Process, Request, nullptr));
	CS_NON_SHIPPING_EXPR(DrawRequest(Request));

	Request->bProcessing = true;

	EAsyncTraceType AsyncTraceType = EAsyncTraceType::Single;

	// Test
	if (Request->Method == ECsTraceMethod::Test)
	{
		AsyncTraceType = EAsyncTraceType::Test;
	}
	// Single
	else
	if (Request->Method == ECsTraceMethod::Single)
	{
		AsyncTraceType = EAsyncTraceType::Single;
	}
	// Multi
	else
	if (Request->Method == ECsTraceMethod::Multi)
	{
		AsyncTraceType = EAsyncTraceType::Multi;
	}

	// Request Members
	const ECsTraceType& Type	 = Request->Type;
	const ECsTraceMethod& Method = Request->Method;
	const ECsTraceQuery& Query	 = Request->Query;

	const FVector& Start	  = Request->Start;
	const FVector& End		  = Request->End;
	ECollisionChannel Channel = Request->Channel;
	const FName& ProfileName  = Request->ProfileName;

	const FCollisionShape& Shape					= Request->Shape;
	const FCollisionQueryParams& Params				= Request->Params;
	const FCollisionObjectQueryParams& ObjectParams = Request->ObjectParams;
	const FCollisionResponseParams& ResponseParams	= Request->ResponseParams;

	const FString& TraceMethodAsString = EMCsTraceMethod::Get().ToString(Method);
	
	// Line
	if (Type == ECsTraceType::Line)
	{
		// AsyncLineTraceByChannel
		if (Query == ECsTraceQuery::Channel)
			Request->CopyHandle(CurrentWorld->AsyncLineTraceByChannel(AsyncTraceType, Start, End, Channel, Params, ResponseParams, &TraceDelegate));
		// AsyncLineTraceByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(CurrentWorld->AsyncLineTraceByObjectType(AsyncTraceType, Start, End, ObjectParams, Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Line Trace %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

			CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr));
			DeallocateRequest(Request);
			return false;
		}
	}
	// Sweep
	else
	if (Type == ECsTraceType::Sweep)
	{
		FQuat Quat = Request->Rotation.Quaternion();

		// AsyncSweepByChannel
		if (Query == ECsTraceQuery::Channel)
			Request->CopyHandle(CurrentWorld->AsyncSweepByChannel(AsyncTraceType, Start, End, Quat, Channel, Shape, Params,  ResponseParams, &TraceDelegate));
		// AsyncSweepByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(CurrentWorld->AsyncSweepByObjectType(AsyncTraceType, Start, End, Quat, ObjectParams, Shape, Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Sweep %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

			CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr));
			DeallocateRequest(Request);
			return false;
		}
	}
	// Overlap
	else
	if (Type == ECsTraceType::Overlap)
	{
		FQuat Quat = Request->Rotation.Quaternion();

		// AsyncOverlapByChannel
		if (Query == ECsTraceQuery::Channel)
			Request->CopyHandle(CurrentWorld->AsyncOverlapByChannel(Start, Quat, Channel, Shape, Params, ResponseParams, &OverlapDelegate));
		// AsyncOverlapByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(CurrentWorld->AsyncOverlapByObjectType(Start, Quat, ObjectParams, Shape, Params, &OverlapDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Overlap %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

			CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr));
			DeallocateRequest(Request);
			return false;
		}
	}
	// OverlapBlocking
	else
	if (Type == ECsTraceType::OverlapBlocking)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Overap Blocking Method."), *Context);

		CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr));
		DeallocateRequest(Request);
		return false;
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Type: %s is NOT Valid. Discarding Request."), *Context, EMCsTraceType::Get().ToChar(Type));

		CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr));
		DeallocateRequest(Request);
		return false;
	}
	return true;
}

void UCsManager_Trace::DrawRequest(const RequestType* Request) const
{
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceRequests))
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		const FCollisionShape& Shape = Request->Shape;
		const FVector& Start		 = Request->Start;
		const FVector& End			 = Request->End;

		Settings->Manager_Trace.Debug.DrawRequest.Draw(GetWorld(), Start, End, &Shape);
	}
}

#undef RequestType

#pragma endregion Request

// Response
#pragma region

#define ResponseType NCsTrace::NResponse::FResponse
ResponseType* UCsManager_Trace::AllocateResponse()
{
#undef ResponseType

	typedef NCsTrace::NResponse::FResource ResponseContainerType;

	ResponseContainerType* Container = Manager_Response.Allocate();

	return Container->Get();
}

#define ResponseType NCsTrace::NResponse::FResponse
void UCsManager_Trace::DeallocateResponse(ResponseType* Response)
{
#undef ResponseType

	Response->Reset();
	Manager_Response.DeallocateAt(Response->GetIndex());
}

void UCsManager_Trace::OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum)
{
	using namespace NCsManagerTrace::NCached;

	const FString& Context = Str::OnTraceResponse;

	typedef NCsTrace::NRequest::FRequest RequestType;
	typedef NCsTrace::NResponse::FResponse ResponseType;

	// Get Request
	RequestType* Request = PendingRequests.Get(Handle);
	// Setup Response
	ResponseType* Response = AllocateResponse();

	Response->bResult	  = Datum.OutHits.Num() > CS_EMPTY && Datum.OutHits[CS_FIRST].bBlockingHit;
	Response->ElapsedTime = CurrentWorld->GetTimeSeconds() - Request->StartTime;

	// Copy Datum
	const int32 Count = Datum.OutHits.Num();

	Response->OutHits.Reset(FMath::Max(Response->OutHits.Max(), Count));

	for (FHitResult& HitResult : Datum.OutHits)
	{
		Response->OutHits.AddDefaulted();
		Response->OutHits.Last() = HitResult;
	}
	
#if !UE_BUILD_SHIPPING
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceResponses))
	{
		if (Response->bResult)
		{
			// Sphere around Start
			DrawDebugSphere(CurrentWorld, Response->OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(CurrentWorld, Response->OutHits[CS_FIRST].TraceStart, Response->OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
		}
	}
#endif // #if !UE_BUILD_SHIPPING

	Request->Response = Response;

	// Broadcast Response
	Request->OnResponse_AsyncEvent.Broadcast(Response);

	Request->bProcessing = false;
	Request->bCompleted = true;
}

void UCsManager_Trace::OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum)
{
	typedef NCsTrace::NRequest::FRequest RequestType;
	typedef NCsTrace::NResponse::FResponse ResponseType;

	// Get Request
	RequestType* Request = PendingRequests.Get(Handle);
	// Setup Response
	ResponseType* Response = AllocateResponse();

	Response->bResult	  = Datum.OutOverlaps.Num() > CS_EMPTY && Datum.OutOverlaps[CS_FIRST].bBlockingHit;
	Response->ElapsedTime = CurrentWorld->GetTimeSeconds() - Request->StartTime;

	// Copy Datum
	const int32 Count = Datum.OutOverlaps.Num();

	Response->OutOverlaps.Reset(FMath::Max(Response->OutOverlaps.Max(), Count));

	for (FOverlapResult& OverlapResult : Datum.OutOverlaps)
	{
		Response->OutOverlaps.AddDefaulted();
		Response->OutOverlaps.Last() = OverlapResult;
	}

#if !UE_BUILD_SHIPPING
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceResponses))
	{
		/*
		if (Response->bResult)
		{
			// Sphere around Start
			DrawDebugSphere(CurrentWorld, Response->OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(CurrentWorld, Response->OutHits[CS_FIRST].TraceStart, Response->OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
		}
		*/
	}
#endif // #if !UE_BUILD_SHIPPING
}

#define RequestType NCsTrace::NRequest::FRequest
#define ResponseType NCsTrace::NResponse::FResponse
void UCsManager_Trace::DrawResponse(const RequestType* Request, const ResponseType* Response) const
{
#undef RequestType
#undef ResponseType

	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceRequests))
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		const FCollisionShape& Shape = Request->Shape;
		const FVector& Start		 = Request->Start;
		const FVector& End			 = Request->End;

		const FHitResult& Hit = Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

		Settings->Manager_Trace.Debug.DrawResponse.Draw(GetWorld(), Start, End, &Shape, Hit);
	}
}

#pragma endregion Response

#define ResponseType NCsTrace::NResponse::FResponse
#define RequestType NCsTrace::NRequest::FRequest
ResponseType* UCsManager_Trace::Trace(RequestType* Request)
{
	CS_SCOPED_TIMER_NAMESPACE_2(NCsManagerTrace, NScopedTimer, Trace);

	using namespace NCsManagerTrace::NCached;

	const FString& Context = Str::Trace;

	checkf(Request, TEXT("%s: Request is NULL."), *Context);

	check(Request->IsValidChecked(Context));

	Request->StartTime = CurrentWorld->GetTimeSeconds();

	CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Receive, Request, nullptr));

	bool AddPending = !Request->bForce && ThisFrameCountInfo.TotalCount >= MaxRequestsProcessedPerTick;

	// TODO: Print warning for a normal trace moved to Async
	if (AddPending && !Request->bAsync)
	{
		DeallocateRequest(Request);
		UE_LOG(LogCs, Warning, TEXT("%s: Reached MaxRequestsProcessedPerTick: %d and Request is NOT Async. Abandoning Request."), *Context, MaxRequestsProcessedPerTick);
		return nullptr;
	}

	// Async
	if (Request->bAsync ||
		AddPending)
	{
		// if NOT Pending, Start Async
		if (!AddPending)
		{
			// if Successful in processing Request, EXIT
			if (ProcessAsyncRequest(Request))
			{
				PendingRequests.Add(Request);
				IncrementTraceCount(Request);
				return nullptr;
			}
		}

		// ADD Pending Request
		PendingRequests.Add(Request);
		return nullptr;
	}
	// Normal
	else
	{
		CS_NON_SHIPPING_EXPR(DrawRequest(Request));

		ResponseType* Response = AllocateResponse();
		Response->QueueDeallocate();

		Response->ElapsedTime = CurrentWorld->GetTimeSeconds() - Request->StartTime;

		// Request Members
		const ECsTraceType& Type	 = Request->Type;
		const ECsTraceMethod& Method = Request->Method;
		const ECsTraceQuery& Query	 = Request->Query;

		const FVector& Start	  = Request->Start;
		const FVector& End		  = Request->End;
		ECollisionChannel Channel = Request->Channel;
		const FName& ProfileName  = Request->ProfileName;

		const FCollisionShape& Shape					= Request->Shape;
		const FCollisionQueryParams& Params				= Request->Params;
		const FCollisionObjectQueryParams& ObjectParams = Request->ObjectParams;
		const FCollisionResponseParams& ResponseParams	= Request->ResponseParams;

		// Response Members
		TArray<FHitResult>& OutHits			= Response->OutHits;
		TArray<FOverlapResult>& OutOverlaps = Response->OutOverlaps;

		// Line
		if (Type == ECsTraceType::Line)
		{
			// Test
			if (Method == ECsTraceMethod::Test)
			{
				// LineTraceTestByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->LineTraceTestByChannel(Start, End, Channel, Params, ResponseParams);
				// LineTraceTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->LineTraceTestByObjectType(Start, End, ObjectParams, Params);
				// LineTraceTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->LineTraceTestByProfile(Start, End, ProfileName, Params);
			}
			// Single
			else
			if (Method == ECsTraceMethod::Single)
			{
				OutHits.AddDefaulted();

				// LineTraceSingleByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->LineTraceSingleByChannel(OutHits[CS_FIRST], Start, End, Channel, Params, ResponseParams);
				// LineTraceSingleByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->LineTraceSingleByObjectType(OutHits[CS_FIRST], Start, End, ObjectParams, Params);
				// LineTraceSingleByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->LineTraceSingleByProfile(OutHits[CS_FIRST], Start, End, ProfileName, Params);
			}
			// Multi
			else
			if (Method == ECsTraceMethod::Multi)
			{
				// LineTraceMultiByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->LineTraceMultiByChannel(OutHits, Start, End, Channel, Params, ResponseParams);
				// LineTraceMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->LineTraceMultiByObjectType(OutHits, Start, End, ObjectParams, Params);
				// LineTraceMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);
			}
		}
		// Sweep
		else
		if (Request->Type == ECsTraceType::Sweep)
		{
			FQuat Quat = Request->Rotation.Quaternion();

			// Test
			if (Method == ECsTraceMethod::Test)
			{
				// SweepTestByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->SweepTestByChannel(Start, End, Quat, Channel, Shape, Params, ResponseParams);
				// SweepTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->SweepTestByObjectType(Start, End, Quat, ObjectParams, Shape, Params);
				// SweepTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->SweepTestByProfile(Start, End, Quat, ProfileName, Shape, Params);
			}
			// Single
			else
			if (Method == ECsTraceMethod::Single)
			{
				OutHits.AddDefaulted();

				// SweepSingleByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->SweepSingleByChannel(OutHits[CS_FIRST], Start, End, Quat, Channel, Shape, Params, ResponseParams);
				// SweepSingleByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->SweepSingleByObjectType(OutHits[CS_FIRST], Start, End, Quat, ObjectParams, Shape, Params);
				// SweepSingleByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->SweepSingleByProfile(OutHits[CS_FIRST], Start, End, Quat, ProfileName, Shape, Params);
			}
			// Multi
			else
			if (Method == ECsTraceMethod::Multi)
			{
				// SweepMultiByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->SweepMultiByChannel(OutHits, Start, End, Quat, Channel, Shape, Params, ResponseParams);
				// SweepMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->SweepMultiByObjectType(OutHits, Start, End, Quat, ObjectParams, Shape, Params);
				// SweepMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->SweepMultiByProfile(OutHits, Start, End, Quat, ProfileName, Shape, Params);
			}
		}
		// Overlap
		else
		if (Request->Type == ECsTraceType::Overlap)
		{
			FQuat Quat = Request->Rotation.Quaternion();

			// Test
			if (Method == ECsTraceMethod::Test)
			{
				// OverlapAnyTestByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->OverlapAnyTestByChannel(Start, Quat, Channel, Shape, Params, ResponseParams);
				// OverlapAnyTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->OverlapAnyTestByObjectType(Start, Quat, ObjectParams, Shape, Params);
				// OverlapAnyTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->OverlapAnyTestByProfile(Start, Quat, ProfileName, Shape, Params);
			}
			// Single
			else
			if (Method == ECsTraceMethod::Single)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::Trace: There is NO Overlap Single Method. Use TraceMethod: Test or Multi."));
				DeallocateResponse(Response);
				DeallocateRequest(Request);
				return nullptr;
			}
			// Multi
			else
			if (Method == ECsTraceMethod::Multi)
			{
				// OverlapMultiByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->OverlapMultiByChannel(OutOverlaps, Start, Quat, Channel, Shape, Params, ResponseParams);
				// OverlapMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = CurrentWorld->OverlapMultiByObjectType(OutOverlaps, Start, Quat, ObjectParams, Shape, Params);
				// OverlapMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->OverlapMultiByProfile(OutOverlaps, Start, Quat, ProfileName, Shape, Params);
			}
		}
		// OverlapBlocking
		else
		if (Request->Type == ECsTraceType::OverlapBlocking)
		{
			FQuat Quat = Request->Rotation.Quaternion();

			// Test
			if (Method == ECsTraceMethod::Test)
			{
				// OverlapBlockingTestByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = CurrentWorld->OverlapBlockingTestByChannel(Start, Quat, Channel, Shape, Params, ResponseParams);
				else
				if (Query == ECsTraceQuery::ObjectType)
				{
					UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::Trace: There is NO Overlap Blocking Test Object Method. Use TraceQuery: Channel or Profile."));
					DeallocateResponse(Response);
					DeallocateRequest(Request);
					return nullptr;
				}
				// OverlapBlockingTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = CurrentWorld->OverlapBlockingTestByProfile(Start, Quat, ProfileName, Shape, Params);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: There is NO Overlap Blocking %s Method. Use TraceMethod: Test."), EMCsTraceMethod::Get().ToChar(Method), *Context);
				DeallocateResponse(Response);
				DeallocateRequest(Request);
				return nullptr;
			}
		}

		IncrementTraceCount(Request);

		CS_NON_SHIPPING_EXPR(LogTransaction(Context, ECsTraceTransaction::Complete, Request, Response));
		CS_NON_SHIPPING_EXPR(DrawResponse(Request, Response));

		DeallocateRequest(Request);
		return Response;
	}
	DeallocateRequest(Request);
	return nullptr;
}
#undef ResponseType
#undef RequestType

#define RequestType NCsTrace::NRequest::FRequest
#define ResponseType NCsTrace::NResponse::FResponse
void UCsManager_Trace::LogTransaction(const FString& Context, const ECsTraceTransaction& Transaction, RequestType* Request, ResponseType* Response)
{
#undef RequestType
#undef ResponseType

	if (CS_CVAR_LOG_IS_SHOWING(LogManagerTraceTransactions))
	{
		const FString& TransactionAsString = NCsTraceTransaction::ToActionString(Transaction);

		// Request
		const ECsTraceType& Type	 = Request->Type;
		const ECsTraceMethod& Method = Request->Method;
		const ECsTraceQuery& Query	 = Request->Query;

		UE_LOG(LogCs, Warning, TEXT("%s: %s Trace: %s %s %s."), *Context, *TransactionAsString, EMCsTraceType::Get().ToChar(Type), EMCsTraceMethod::Get().ToChar(Method), EMCsTraceQuery::Get().ToChar(Query));
		UE_LOG(LogCs, Warning, TEXT("- Request"));
		UE_LOG(LogCs, Warning, TEXT("-- Index: %d"), Request->Index);
		UE_LOG(LogCs, Warning, TEXT("-- bForce: %s"), Request->bForce ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- StartTime: %f"), Request->StartTime);
		UE_LOG(LogCs, Warning, TEXT("-- StaleTime: %f"), Request->StaleTime);

		if (UObject* Caller = Request->GetCaller())
		{
			UE_LOG(LogCs, Warning, TEXT("-- Caller: %s Class: %s"), *(Caller->GetName()), *(Caller->GetClass()->GetName()));

			if (ICsUniqueObject* UniqueObject = Request->UniqueObject)
			{
				const FCsUniqueObjectId& Id = UniqueObject->GetId();

				UE_LOG(LogCs, Warning, TEXT("-- UniqueObject: %s"), *(Id.Id.ToString()));
			}
		}

		UE_LOG(LogCs, Warning, TEXT("-- bAsync: %f"), Request->bAsync ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- Start: %s"), *(*Request->Start.ToString()));

		// Line | Sweep
		if (Type == ECsTraceType::Line ||
			Type == ECsTraceType::Sweep)
		{
			UE_LOG(LogCs, Warning, TEXT("-- End: %s"), *(*Request->End.ToString()));
		}
		// Overlap | OverlapBlocking
		if (Type == ECsTraceType::Overlap ||
			Type == ECsTraceType::OverlapBlocking)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Rotation: %s"), *(*Request->Rotation.ToString()));
		}

		// Channel
		if (Query == ECsTraceQuery::Channel)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Channel: %s"), EMCsCollisionChannel::Get().ToChar((ECollisionChannel)Request->Channel));
		}
		// ObjectType
		if (Query == ECsTraceQuery::ObjectType)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Object Params"));

			for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
			{
				if (Request->ObjectParams.IsValidObjectQuery(Channel))
				{
					UE_LOG(LogCs, Warning, TEXT("--- Channel: %s"), EMCsCollisionChannel::Get().ToChar(Channel));
				}
			}
		}
		// Profile
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Profile: %s"), *(Request->ProfileName.ToString()));
		}

		// Shape
		if (Type != ECsTraceType::Line)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Shape: %s"), EMCsCollisionShape::Get().ToChar(Request->Shape.ShapeType));
		}
 
		// Params
		{
			const FCollisionQueryParams& Params = Request->Params;

			UE_LOG(LogCs, Warning, TEXT("-- Params"));
			UE_LOG(LogCs, Warning, TEXT("--- TraceTag: %s"), *(Params.TraceTag.ToString()));
			UE_LOG(LogCs, Warning, TEXT("--- OwnerTag: %s"), *(Params.OwnerTag.ToString()));
			UE_LOG(LogCs, Warning, TEXT("--- bTraceComplex: %s"), Params.bTraceComplex ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCs, Warning, TEXT("--- bFindInitialOverlaps: %s"), Params.bFindInitialOverlaps ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCs, Warning, TEXT("--- bReturnFaceIndex: %s"), Params.bReturnFaceIndex ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCs, Warning, TEXT("--- bReturnPhysicalMaterial: %s"), Params.bReturnPhysicalMaterial ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCs, Warning, TEXT("--- bIgnoreBlocks: %s"), Params.bIgnoreBlocks ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCs, Warning, TEXT("--- bIgnoreTouches: %s"), Params.bIgnoreTouches ? TEXT("True") : TEXT("False"));
		}

		// Response Params
		if (Query == ECsTraceQuery::Channel)
		{
			const FCollisionResponseParams& ResponseParams		 = Request->ResponseParams;
			const FCollisionResponseContainer& ResponseContainer = ResponseParams.CollisionResponse;

			UE_LOG(LogCs, Warning, TEXT("-- ResponseParams"));
			
			// Log Response for the appropriate Channel
			for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
			{
				const ECollisionResponse& CollisionResponse = ResponseContainer.GetResponse(Channel);

				// Overlap | Block
				if (CollisionResponse != ECollisionResponse::ECR_Ignore)
				{
					UE_LOG(LogCs, Warning, TEXT("--- %s: %s"), EMCsCollisionChannel::Get().ToChar(Channel), EMCollisionResponse::Get().ToChar(CollisionResponse));
				}
			}
		}

		// Response
		if (Response)
		{
			TArray<FHitResult>& OutHits			= Response->OutHits;
			TArray<FOverlapResult>& OutOverlaps = Response->OutOverlaps;

			UE_LOG(LogCs, Warning, TEXT("- Response"));
			UE_LOG(LogCs, Warning, TEXT("-- Index: %d"), Response->Index);

			// Line | Sweep
			if (Type == ECsTraceType::Line ||
				Type == ECsTraceType::Sweep)
			{
				// Single | Multi
				if (Method == ECsTraceMethod::Single ||
					Method == ECsTraceMethod::Multi)
				{
					const int32 Count = Response->OutHits.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FHitResult& Hit = OutHits[I];

						UE_LOG(LogCs, Warning, TEXT("-- OutHits[%d]"), I);
						UE_LOG(LogCs, Warning, TEXT("--- bBlockingHit: %s"), Hit.bBlockingHit ? TEXT("True") : TEXT("False"));
						UE_LOG(LogCs, Warning, TEXT("--- bStartPenetrating: %s"), Hit.bStartPenetrating ? TEXT("True") : TEXT("False"));
						UE_LOG(LogCs, Warning, TEXT("--- FaceIndex: %d"), Hit.FaceIndex);
						UE_LOG(LogCs, Warning, TEXT("--- Time: %f"), Hit.Time);
						UE_LOG(LogCs, Warning, TEXT("--- Distance: %f"), Hit.Distance);
						UE_LOG(LogCs, Warning, TEXT("--- Location: %s"), *(Hit.Location.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- ImpactPoint: %s"), *(Hit.ImpactPoint.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- Normal: %s"), *(Hit.Normal.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- ImpactNormal: %s"), *(Hit.ImpactNormal.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- TraceStart: %s"), *(Hit.TraceStart.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- TraceEnd: %s"), *(Hit.TraceEnd.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- PenetrationDepth: %f"), Hit.PenetrationDepth);
						UE_LOG(LogCs, Warning, TEXT("--- Item: %d"), Hit.Item);

						UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;

						UE_LOG(LogCs, Warning, TEXT("--- PhysMaterial: %s"), PhysMaterial ? *(PhysMaterial->GetName()) : TEXT("None"));
						UE_LOG(LogCs, Warning, TEXT("--- Actor: %s"), Hit.GetActor() ? *(Hit.GetActor()->GetName()) : TEXT("None"));
						UE_LOG(LogCs, Warning, TEXT("--- Component: %s"), Hit.GetComponent() ? *(Hit.GetComponent()->GetName()) : TEXT("None"));
						UE_LOG(LogCs, Warning, TEXT("--- BoneName: %s"), *(Hit.BoneName.ToString()));
						UE_LOG(LogCs, Warning, TEXT("--- MyBoneName: %s"), *(Hit.MyBoneName.ToString()));
					}
				}
			}
			// Overlap
			if (Type == ECsTraceType::Overlap)
			{
				// Multi
				if (Method == ECsTraceMethod::Multi)
				{
					const int32 Count = Response->OutOverlaps.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FOverlapResult& Overlap = OutOverlaps[I];

						UE_LOG(LogCs, Warning, TEXT("-- OutOverlaps[%d]"), I);
						UE_LOG(LogCs, Warning, TEXT("--- bBlockingHit: %s"), Overlap.bBlockingHit ? TEXT("True") : TEXT("False"));
						UE_LOG(LogCs, Warning, TEXT("--- ItemIndex: %d"), Overlap.ItemIndex);
						UE_LOG(LogCs, Warning, TEXT("--- Actor: %s"), Overlap.GetActor() ? *(Overlap.GetActor()->GetName()) : TEXT("None"));
						UE_LOG(LogCs, Warning, TEXT("--- Component: %s"), Overlap.GetComponent() ? *(Overlap.GetComponent()->GetName()) : TEXT("None"));
					}
				}
			}
		}
	}
}