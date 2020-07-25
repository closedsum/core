// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsManager_Trace.h"
#include "CsCore.h"

// CVars
#include "Managers/Trace/CsCVars_Manager_Trace.h"
// Library
#include "Library/CsLibrary_Common.h"

//#include "Game/CsGameState_DEPRECATED.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Trace/CsGetManagerTrace.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsManagerTraceCached
{
	namespace Str
	{
		const FString Trace = TEXT("UCsManager_Trace::Trace");
		const FString ProcessAsyncRequest = TEXT("UCsManager_Trace::ProcessAsyncRequest");
		const FString OnTraceResponse = TEXT("UCsManager_Trace::OnTraceResponse");
	}
}

#pragma endregion Cache

// static initializations
UCsManager_Trace* UCsManager_Trace::s_Instance;
bool UCsManager_Trace::s_bShutdown = false;

UCsManager_Trace::UCsManager_Trace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	RequestsProcessedPerTick = 64;

	TraceDelegate.BindUObject(this, &UCsManager_Trace::OnTraceResponse);
	OverlapDelegate.BindUObject(this, &UCsManager_Trace::OnOverlapResponse);
}

// Singleton
#pragma region

/*static*/ UCsManager_Trace* UCsManager_Trace::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerTrace(InRoot)->GetManager_Trace();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Trace::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerTrace(InRoot)->GetManager_Trace() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

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
	checkf(InRoot, TEXT("UCsManager_Trace::Get_GetManagerDamage: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Trace::Get_GetManagerDamage: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Trace::Get_GetManagerDamage: Manager_Singleton is NULL."));

	ICsGetManagerTrace* GetManagerTrace = Cast<ICsGetManagerTrace>(Manager_Singleton);

	checkf(GetManagerTrace, TEXT("UCsManager_Trace::Get_GetManagerDamage: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerTrace."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

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
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Trace* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Trace from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Trace::Initialize()
{
	// TODO: Get PoolSize from config

	static const int32 PoolSize = 256;
	
	// Request
	{
		Manager_Request.CreatePool(PoolSize);

		const TArray<FCsResource_TraceRequest*>& Pool = Manager_Request.GetPool();

		for (FCsResource_TraceRequest* Container : Pool)
		{
			FCsTraceRequest* R = Container->Get();
			const int32& Index = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Response
	{
		Manager_Response.CreatePool(PoolSize);

		const TArray<FCsResource_TraceResponse*>& Pool = Manager_Response.GetPool();

		for (FCsResource_TraceResponse* Container : Pool)
		{
			FCsTraceResponse* R = Container->Get();
			const int32& Index  = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
}

void UCsManager_Trace::CleanUp()
{
	Manager_Request.Shutdown();
	Manager_Response.Shutdown();
}

	// Root
#pragma region

void UCsManager_Trace::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Trace::OnTick(const float &DeltaSeconds)
{
	// Reset TraceCountThisFrame
	ThisFrameCountInfo.Reset();

	// Process Requests
	{
		const int32 ProcessCountMax = FMath::Max(0, RequestsProcessedPerTick - (int32)ThisFrameCountInfo.TotalCount);
		const int32 Count			= FMath::Min(Manager_Request.GetAllocatedSize(), ProcessCountMax);

		const float CurrentTime = GetWorld()->GetTimeSeconds();

		int32 I = 0;

		TCsDoubleLinkedList<FCsResource_TraceRequest*>* Current = Manager_Request.GetAllocatedHead();
		TCsDoubleLinkedList<FCsResource_TraceRequest*>* Next	= Current;

		while (Next)
		{
			Current								= Next;
			FCsResource_TraceRequest* Container = **Current;
			Next								= Current->GetNextLink();

			FCsTraceRequest* Request = Container->Get();

			// If Processing, SKIP
			if (Request->bProcessing)
				continue;
			// If COMPLETED, Remove
			if (Request->bCompleted)
			{
				if (FCsTraceResponse* Response = Request->Response)
				{
					Request->OnResponse_Event.Broadcast(Response);
				}
				PendingRequests.Remove(Request);
				DeallocateRequest(Request);
				continue;
			}
			// Check to remove STALE Request
			if (Request->StaleTime > 0.0f &&
				CurrentTime - Request->StartTime >= Request->StaleTime)
			{
				PendingRequests.Remove(Request);
				DeallocateRequest(Request);
				continue;
			}
			// PROCESS Request
			if (I < Count)
			{
				ProcessAsyncRequest(Request);
				IncrementTraceCount(Request);
			}
			++I;
		}
	}
	// Process Responses
	{
		TCsDoubleLinkedList<FCsResource_TraceResponse*>* Current = Manager_Response.GetAllocatedHead();
		TCsDoubleLinkedList<FCsResource_TraceResponse*>* Next	= Current;

		while (Next)
		{
			Current							     = Next;
			FCsResource_TraceResponse* Container = **Current;
			Next								 = Current->GetNextLink();

			FCsTraceResponse* Response = Container->Get();

			// Check to deallocate Response
			if (Response->ShouldDeallocate())
			{
				DeallocateResponse(Response);
			}
		}
	}
}

void UCsManager_Trace::IncrementTraceCount(FCsTraceRequest* Request)
{
	// Lifetime
	LifetimeCountInfo.Increment(Request);
	// Frame
	ThisFrameCountInfo.Increment(Request);
}

// Request
#pragma region

FCsTraceRequest* UCsManager_Trace::AllocateRequest()
{
	FCsResource_TraceRequest* Container = Manager_Request.Allocate();

	return Container->Get();
}

void UCsManager_Trace::DeallocateRequest(FCsTraceRequest* Request)
{
	if (FCsTraceResponse* Response = Request->Response)
		DeallocateResponse(Response);

	Request->Reset();
	Manager_Request.DeallocateAt(Request->GetIndex());
}

bool UCsManager_Trace::ProcessAsyncRequest(FCsTraceRequest* Request)
{
	using namespace NCsManagerTraceCached;

	const FString& Context = Str::ProcessAsyncRequest;

	checkf(Request, TEXT("%s: Request is NULL."), *Context);

	checkf(Request->IsValid(), TEXT("%s: Request is NOT Valid."), *Context);

#if !UE_BUILD_SHIPPING
	LogTransaction(Context, ECsTraceTransaction::Process, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

#if !UE_BUILD_SHIPPING
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceRequests))
	{
		// Sphere around Start
		DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
		// Line from Start to End
		DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
	}
#endif // #if !UE_BUILD_SHIPPING

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
	const FCollisionResponseParams& ResponseParam	= Request->ResponseParam;

	const FString& TraceMethodAsString = EMCsTraceMethod::Get().ToString(Method);

	// Line
	if (Type == ECsTraceType::Line)
	{
		// AsyncLineTraceByChannel
		if (Query == ECsTraceQuery::Channel)
			Request->CopyHandle(GetWorld()->AsyncLineTraceByChannel(AsyncTraceType, Start, End, Channel, Params, ResponseParam, &TraceDelegate));
		// AsyncLineTraceByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncLineTraceByObjectType(AsyncTraceType, Start, End, ObjectParams, Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Line Trace %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

#if !UE_BUILD_SHIPPING
			LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

			DeallocateRequest(Request);
			return false;
		}
	}
	// Sweep
	else
	if (Type == ECsTraceType::Sweep)
	{
		// AsyncSweepByChannel
		if (Query == ECsTraceQuery::Channel)
			Request->CopyHandle(GetWorld()->AsyncSweepByChannel(AsyncTraceType, Start, End, Channel, Shape, Params,  ResponseParam, &TraceDelegate));
		// AsyncSweepByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncSweepByObjectType(AsyncTraceType, Start, End, ObjectParams, Shape, Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Sweep %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

#if !UE_BUILD_SHIPPING
			LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

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
			Request->CopyHandle(GetWorld()->AsyncOverlapByChannel(Start, Quat, Channel, Shape, Params, ResponseParam, &OverlapDelegate));
		// AsyncOverlapByObjectType
		else
		if (Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncOverlapByObjectType(Start, Quat, ObjectParams, Shape, Params, &OverlapDelegate));
		// NOT SUPPORTED
		else
		if (Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Overlap %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *Context, *TraceMethodAsString);

#if !UE_BUILD_SHIPPING
			LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

			DeallocateRequest(Request);
			return false;
		}
	}
	// OverlapBlocking
	else
	if (Type == ECsTraceType::OverlapBlocking)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: There is NO Async Overap Blocking Method."), *Context);

#if !UE_BUILD_SHIPPING
		LogTransaction(Context, ECsTraceTransaction::Discard, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

		DeallocateRequest(Request);
	}
	return true;
}

#pragma endregion Request

// Response
#pragma region

FCsTraceResponse* UCsManager_Trace::AllocateResponse()
{
	FCsResource_TraceResponse* Container = Manager_Response.Allocate();

	return Container->Get();
}

void UCsManager_Trace::DeallocateResponse(FCsTraceResponse* Response)
{
	Response->Reset();
	Manager_Response.DeallocateAt(Response->GetIndex());
}

void UCsManager_Trace::OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum)
{
	const TCsTraceHandleId& HandleId = Handle._Handle;
	// Get Request
	FCsTraceRequest* Request = PendingRequests.Get(Handle);
	// Setup Response
	FCsTraceResponse* Response = AllocateResponse();

	Response->bResult	  = Datum.OutHits.Num() > CS_EMPTY && Datum.OutHits[CS_FIRST].bBlockingHit;
	Response->ElapsedTime = GetWorld()->GetTimeSeconds() - Request->StartTime;

	// Copy Datum
	const int32 Count = Datum.OutHits.Num();

	Response->OutHits.Reserve(FMath::Max(Response->OutHits.Max(), Count));

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
			DrawDebugSphere(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, Response->OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
		}
	}
#endif // #if !UE_BUILD_SHIPPING

	LogTransaction(NCsManagerTraceCached::Str::OnTraceResponse, ECsTraceTransaction::Complete, Request, Response);

	Request->Response = Response;

	// Broadcast Response
	Request->OnResponse_AsyncEvent.Broadcast(Response);

	Request->bProcessing = false;
	Request->bCompleted = true;
}

void UCsManager_Trace::OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum)
{
}

#pragma endregion Response

FCsTraceResponse* UCsManager_Trace::Trace(FCsTraceRequest* Request)
{
	using namespace NCsManagerTraceCached;

	const FString& Context = Str::Trace;

	checkf(Request, TEXT("%s: Request is NULL."), *Context);

	Request->StartTime = GetWorld()->GetTimeSeconds();

#if !UE_BUILD_SHIPPING
	LogTransaction(Context, ECsTraceTransaction::Receive, Request, nullptr);
#endif // #if !UE_BUILD_SHIPPING

	bool AddPending = !Request->bForce && ThisFrameCountInfo.TotalCount >= RequestsProcessedPerTick;

	// TODO: Print warning for a normal trace moved to Async
	if (AddPending && !Request->bAsync)
	{
		DeallocateRequest(Request);
		UE_LOG(LogCs, Warning, TEXT("%s: Reached maximum RequestsProcessedPerTick: %d and Request is NOT Async. Abandoning Request."), *Context, RequestsProcessedPerTick);
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
#if !UE_BUILD_SHIPPING
		if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceRequests))
		{
			// Sphere around Start
			DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
		}
#endif // #if !UE_BUILD_SHIPPING

		FCsTraceResponse* Response = AllocateResponse();
		Response->QueueDeallocate();

		Response->ElapsedTime = GetWorld()->GetTimeSeconds() - Request->StartTime;

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
		const FCollisionResponseParams& ResponseParam	= Request->ResponseParam;

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
					Response->bResult = GetWorld()->LineTraceTestByChannel(Start, End, Channel, Params, ResponseParam);
				// LineTraceTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceTestByObjectType(Start, End, ObjectParams, Params);
				// LineTraceTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceTestByProfile(Start, End, ProfileName, Params);
			}
			// Single
			else
			if (Method == ECsTraceMethod::Single)
			{
				OutHits.AddDefaulted();

				// LineTraceSingleByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->LineTraceSingleByChannel(OutHits[CS_FIRST], Start, End, Channel, Params, ResponseParam);
				// LineTraceSingleByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceSingleByObjectType(OutHits[CS_FIRST], Start, End, ObjectParams, Params);
				// LineTraceSingleByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceSingleByProfile(OutHits[CS_FIRST], Start, End, ProfileName, Params);
			}
			// Multi
			else
			if (Method == ECsTraceMethod::Multi)
			{
				// LineTraceMultiByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->LineTraceMultiByChannel(OutHits, Start, End, Channel, Params, ResponseParam);
				// LineTraceMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, End, ObjectParams, Params);
				// LineTraceMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);
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
					Response->bResult = GetWorld()->SweepTestByChannel(Start, End, Quat, Channel, Shape, Params, ResponseParam);
				// SweepTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->SweepTestByObjectType(Start, End, Quat, ObjectParams, Shape, Params);
				// SweepTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->SweepTestByProfile(Start, End, Quat, ProfileName, Shape, Params);
			}
			// Single
			else
			if (Method == ECsTraceMethod::Single)
			{
				OutHits.AddDefaulted();

				// SweepSingleByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->SweepSingleByChannel(OutHits[CS_FIRST], Start, End, Quat, Channel, Shape, Params, ResponseParam);
				// SweepSingleByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->SweepSingleByObjectType(OutHits[CS_FIRST], Start, End, Quat, ObjectParams, Shape, Params);
				// SweepSingleByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->SweepSingleByProfile(OutHits[CS_FIRST], Start, End, Quat, ProfileName, Shape, Params);
			}
			// Multi
			else
			if (Method == ECsTraceMethod::Multi)
			{
				// SweepMultiByChannel
				if (Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->SweepMultiByChannel(OutHits, Start, End, Quat, Channel, Shape, Params, ResponseParam);
				// SweepMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, Quat, ObjectParams, Shape, Params);
				// SweepMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->SweepMultiByProfile(OutHits, Start, End, Quat, ProfileName, Shape, Params);
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
					Response->bResult = GetWorld()->OverlapAnyTestByChannel(Start, Quat, Channel, Shape, Params, ResponseParam);
				// OverlapAnyTestByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->OverlapAnyTestByObjectType(Start, Quat, ObjectParams, Shape, Params);
				// OverlapAnyTestByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->OverlapAnyTestByProfile(Start, Quat, ProfileName, Shape, Params);
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
					Response->bResult = GetWorld()->OverlapMultiByChannel(OutOverlaps, Start, Quat, Channel, Shape, Params, ResponseParam);
				// OverlapMultiByObjectType
				else
				if (Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->OverlapMultiByObjectType(OutOverlaps, Start, Quat, ObjectParams, Shape, Params);
				// OverlapMultiByProfile
				else
				if (Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->OverlapMultiByProfile(OutOverlaps, Start, Quat, ProfileName, Shape, Params);
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
					Response->bResult = GetWorld()->OverlapBlockingTestByChannel(Start, Quat, Channel, Shape, Params, ResponseParam);
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
					Response->bResult = GetWorld()->OverlapBlockingTestByProfile(Start, Quat, ProfileName, Shape, Params);
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

#if !UE_BUILD_SHIPPING
		LogTransaction(Context, ECsTraceTransaction::Complete, Request, Response);
#endif // #if !UE_BUILD_SHIPPING

		DeallocateRequest(Request);

#if !UE_BUILD_SHIPPING
		if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawManagerTraceResponses))
		{
			if (Response->bResult)
			{
				// Sphere around Start
				DrawDebugSphere(GetWorld(), OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
				// Line from Start to End
				DrawDebugLine(GetWorld(), OutHits[CS_FIRST].TraceStart, OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
			}
		}
#endif // #if !UE_BUILD_SHIPPING
		return Response;
	}
	DeallocateRequest(Request);
	return nullptr;
}

void UCsManager_Trace::LogTransaction(const FString& Context, const ECsTraceTransaction& Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response)
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerTraceTransactions))
	{
		/*
		const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = FString::Printf(TEXT("%llu"), Item->UniqueId);
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const UCsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : NCsCached::Str::Empty;
		const float CurrentTime				  = GetWorld()->GetTimeSeconds();

		if (Data_Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: %s, Data: %s, and with Data_Actor: %s at %f."), *FunctionName, *TransactionAsString, *ItemName,*Id, *DataName, *DataActorName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: % and Data: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *Id, *DataName, CurrentTime);
		}
		*/
	}
}