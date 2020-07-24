// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsManager_Trace.h"
#include "CsCore.h"

// CVars
#include "CsCVars.h"
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
		const FString ProcessRequest = TEXT("UCsManager_Trace::ProcessRequest");
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

	for (uint8 I = 0; I < CS_POOLED_TRACE_REQUEST_SIZE; ++I)
	{
		Requests[I].Id = I;
	}

	for (uint8 I = 0; I < ECS_TRACE_TYPE_MAX; ++I)
	{
		TraceCountLifetimeByType[I] = 0;
		TraceCountThisFrameByType[I] = 0;

		TMap<TCsTraceRequestId, FCsTraceRequest*> AddMap;
		PendingRequestsByType.Add((ECsTraceType)I, AddMap);
	}

	for (uint8 I = 0; I < ECS_TRACE_METHOD_MAX; ++I)
	{
		TraceCountLifetimeByMethod[I] = 0;
		TraceCountThisFrameByMethod[I] = 0;

		TMap<TCsTraceRequestId, FCsTraceRequest*> AddMap;
		PendingRequestsByMethod.Add((ECsTraceMethod)I, AddMap);
	}

	for (uint8 I = 0; I < ECS_TRACE_QUERY_MAX; ++I)
	{
		TraceCountLifetimeByQuery[I] = 0;
		TraceCountThisFrameByQuery[I] = 0;

		TMap<TCsTraceRequestId, FCsTraceRequest*> AddMap;
		PendingRequestsByQuery.Add((ECsTraceQuery)I, AddMap);
	}

	TraceDelegate.BindUObject(this, &ACsManager_Trace::OnTraceResponse);
	OverlapDelegate.BindUObject(this, &ACsManager_Trace::OnOverlapResponse);
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

	GetManagerTrace->SetManager_Damage(nullptr);
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

/*static*/ ICsGetManagerTrace* UCsManager_Trace::Get_GetManagerDamage(UObject* InRoot)
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
	
	Manager_Request.CreatePool(PoolSize);
	Manager_Response.CreatePool(PoolSize);
}

void UCsManager_Trace::CleanUp()
{
	TraceCountLifetime = 0;
	TraceCountThisFrame = 0;

	for (uint8 I = 0; I < ECS_TRACE_TYPE_MAX; ++I)
	{
		TraceCountLifetimeByType[I] = 0;
		TraceCountThisFrameByType[I] = 0;
	}

	for (uint8 I = 0; I < ECS_TRACE_METHOD_MAX; ++I)
	{
		TraceCountLifetimeByMethod[I] = 0;
		TraceCountThisFrameByMethod[I] = 0;
	}

	for (uint8 I = 0; I < ECS_TRACE_QUERY_MAX; ++I)
	{
		TraceCountLifetimeByQuery[I] = 0;
		TraceCountThisFrameByQuery[I] = 0;
	}

	for (uint8 I = 0; I < CS_POOLED_TRACE_REQUEST_SIZE; ++I)
	{
		Requests[I].Reset();
	}

	PendingRequestHead = nullptr;
	PendingRequestTail = nullptr;

	PendingRequests.Reset();
	PendingRequestsByObjectId.Reset();
	PendingRequestsByType.Reset();
	PendingRequestsByMethod.Reset();
	PendingRequestsByQuery.Reset();
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
	TraceCountThisFrame = 0;

	for (uint8 I = 0; I < ECS_TRACE_TYPE_MAX; ++I)
	{
		TraceCountThisFrameByType[I] = 0;
	}

	for (uint8 I = 0; I < ECS_TRACE_METHOD_MAX; ++I)
	{
		TraceCountThisFrameByMethod[I] = 0;
	}

	for (uint8 I = 0; I < ECS_TRACE_QUERY_MAX; ++I)
	{
		TraceCountThisFrameByQuery[I] = 0;
	}
	// Process Requests
	const int32 ProcessCountMax = FMath::Max(0, RequestsProcessedPerTick - TraceCountThisFrame);

	TArray<TCsTraceRequestId> Keys;
	PendingRequests.GetKeys(Keys);

	const int32 KeyCount = Keys.Num();
	const int32 Count    = FMath::Min(KeyCount, ProcessCountMax);

	const float CurrentTime = GetWorld()->GetTimeSeconds();

	int32 I = 0;

	TLinkedList<FCsTraceRequest*>* Current = PendingRequestHead;

	while (Current)
	{
		FCsTraceRequest* Request = **Current;
		Current					 = PendingRequestHead->GetNextLink();

		// If Processing, SKIP
		if (Request->bProcessing)
			continue;
		// If COMPLETED, Remove
		if (Request->bCompleted)
		{
			RemovePendingRequest(Request);
			continue;
		}
		// Check to remove STALE Request
		if (Request->StaleTime > 0.0f &&
			CurrentTime - Request->StartTime >= Request->StaleTime)
		{
			RemovePendingRequest(Request);
			continue;
		}
		// PROCESS Request
		if (I < Count)
		{
			ProcessRequest(Request);
			IncrementTraceCount(Request);
		}
		++I;
	}
}

void UCsManager_Trace::IncrementTraceCount(FCsTraceRequest* Request)
{
	FCsUniqueObjectId Id;
	const ECsTraceType& Type	 = Request->Type;
	const ECsTraceMethod& Method = Request->Method;
	const ECsTraceQuery& Query	 = Request->Query;

	// Lifetime
	LifetimeCountInfo.Increment(Id, Type, Method, Query);
	// Frame
	ThisFrameCountInfo.Increment(Id, Type, Method, Query);
}

// Request
#pragma region

FCsResource_TraceRequest* UCsManager_Trace::AllocateRequest()
{
	return Manager_Request.Allocate();
}

void ACsManager_Trace::AddPendingRequest(FCsTraceRequest* Request)
{
	if (PendingRequestTail)
	{
		Request->Link.LinkAfter(PendingRequestTail);
		PendingRequestTail = &(Request->Link);
	}
	else
	{
		PendingRequestHead = &(Request->Link);
		PendingRequestTail = PendingRequestHead;
	}

	const TCsTraceRequestId& RequestId = Request->Id;

	PendingRequests.Add(RequestId, Request);

	// TraceId
	const TCsTraceHandleId& HandleId = Request->Handle._Handle;

	if (HandleId != 0)
	{
		PendingRequestsByTraceHandle.Add(HandleId, Request);
	}

	// ObjectId
	if (TMap<TCsTraceRequestId, FCsTraceRequest*>* Map = PendingRequestsByObjectId.Find(Request->CallerId))
	{
		Map->Add(RequestId, Request);
	}
	else
	{
		TMap<TCsTraceRequestId, FCsTraceRequest*> NewMap;
		NewMap.Add(RequestId, Request);
		PendingRequestsByObjectId.Add(Request->CallerId, NewMap);
	}
	// Type
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapType = PendingRequestsByType[Request->Type];
	MapType.Add(RequestId, Request);
	// Method
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapMethod = PendingRequestsByMethod[Request->Method];
	MapMethod.Add(RequestId, Request);
	// Query
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapQuery = PendingRequestsByQuery[Request->Query];
	MapQuery.Add(RequestId, Request);

	// Check if an EXISTING Request should be REPLACED
	if (!Request->bProcessing && Request->ReplacePending)
	{
		const TCsTraceRequestId& PendingRequestId = Request->PendingId;

		if (FCsTraceRequest** PendingRequestPtr = PendingRequests.Find(PendingRequestId))
		{
			FCsTraceRequest* PendingRequest	= *PendingRequestPtr;

			ReplacePendingRequest(PendingRequest, Request);
		}
	}

	// LOG TRANSACTION
}

void ACsManager_Trace::ReplacePendingRequest(FCsTraceRequest* PendingRequest, FCsTraceRequest* Request)
{
	// Update Maps
	const TCsTraceRequestId& PendingRequestId = PendingRequest->Id;

	PendingRequests.Remove(PendingRequestId);
	// TraceId
	const TCsTraceHandleId& PendingHandleId = PendingRequest->Handle._Handle;

	PendingRequestsByTraceHandle.Remove(PendingHandleId);
	// ObjectId
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapId = PendingRequestsByObjectId[PendingRequest->CallerId];
	MapId.Remove(PendingRequestId);
	// Type
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapType = PendingRequestsByType[PendingRequest->Type];
	MapType.Remove(PendingRequestId);
	// Method
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapMethod = PendingRequestsByMethod[PendingRequest->Method];
	MapMethod.Remove(PendingRequestId);
	// Query
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapQuery = PendingRequestsByQuery[PendingRequest->Query];
	MapQuery.Remove(PendingRequestId);

	TLinkedList<FCsTraceRequest*>* PendingLink = &(PendingRequest->Link);

	Request->Link.LinkReplace(PendingLink);

	// Check if Pending Link was the HEAD
	if (PendingLink == PendingRequestHead)
	{
		PendingRequestHead = &(Request->Link);

		if (PendingRequests.Num() == CS_SINGLETON)
		{
			PendingRequestTail = &(Request->Link);
		}
	}

	// LOG

	PendingRequest->Reset();
}

void ACsManager_Trace::RemovePendingRequest(FCsTraceRequest* Request)
{
	// Update Maps
	const TCsTraceRequestId& RequestId = Request->Id;

	PendingRequests.Remove(RequestId);
	// TraceId
	const TCsTraceHandleId& HandleId = Request->Handle._Handle;

	PendingRequestsByTraceHandle.Remove(HandleId);
	// ObjectId
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapId = PendingRequestsByObjectId[Request->CallerId];
	MapId.Remove(RequestId);
	// Type
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapType = PendingRequestsByType[Request->Type];
	MapType.Remove(RequestId);
	// Method
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapMethod = PendingRequestsByMethod[Request->Method];
	MapMethod.Remove(RequestId);
	// Query
	TMap<TCsTraceRequestId, FCsTraceRequest*>& MapQuery = PendingRequestsByQuery[Request->Query];
	MapQuery.Remove(RequestId);

	// LOG TRANSACTION

	// Update HEAD of Queue
	TLinkedList<FCsTraceRequest*>* Link = &(Request->Link);

	if (Link == PendingRequestHead)
	{
		if (PendingRequests.Num() > CS_EMPTY)
		{
			PendingRequestHead = Link->GetNextLink();
		}
		else
		{
			PendingRequestHead = nullptr;
			PendingRequestTail = nullptr;
		}
	}
	Request->Reset();
}

bool UCsManager_Trace::ProcessRequest(FCsResource_TraceRequest* Request)
{
	checkf(Request, TEXT(""));

	FCsTraceRequest* R = Request->Get();

	checkf(R, TEXT(""));

#if !UE_BUILD_SHIPPING
	if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
	{
		// Sphere around Start
		DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
		// Line from Start to End
		DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
	}
#endif // #if !UE_BUILD_SHIPPING

	Request->bProcessing = true;

	EAsyncTraceType AsyncTraceType	   = EAsyncTraceType::Single;
	const FString& TraceMethodAsString = EMCsTraceMethod::Get().ToString(Request->Method);

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

	// Line
	if (Request->Type == ECsTraceType::Line)
	{
		// AsyncLineTraceByChannel
		if (Request->Query == ECsTraceQuery::Channel)
			Request->CopyHandle(GetWorld()->AsyncLineTraceByChannel(AsyncTraceType, Request->Start, Request->End, Request->Channel, Request->Params, Request->ResponseParam, &TraceDelegate));
		// AsyncLineTraceByObjectType
		else
		if (Request->Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncLineTraceByObjectType(AsyncTraceType, Request->Start, Request->End, Request->ObjectParams, Request->Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Line Trace %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *TraceMethodAsString);
			Request->Reset();
			return false;
		}
	}
	// Sweep
	else
	if (Request->Type == ECsTraceType::Sweep)
	{
		// AsyncSweepByChannel
		if (Request->Query == ECsTraceQuery::Channel)
			Request->CopyHandle(GetWorld()->AsyncSweepByChannel(AsyncTraceType, Request->Start, Request->End, Request->Channel, Request->Shape, Request->Params,  Request->ResponseParam, &TraceDelegate));
		// AsyncSweepByObjectType
		else
		if (Request->Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncSweepByObjectType(AsyncTraceType, Request->Start, Request->End, Request->ObjectParams, Request->Shape, Request->Params, &TraceDelegate));
		// NOT SUPPORTED
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Sweep Trace %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *TraceMethodAsString);
			Request->Reset();
			return false;
		}
	}
	// Overlap
	else
	if (Request->Type == ECsTraceType::Overlap)
	{
		// AsyncOverlapByChannel
		if (Request->Query == ECsTraceQuery::Channel)
			Request->CopyHandle(GetWorld()->AsyncOverlapByChannel(Request->Start, Request->Rotation.Quaternion(), Request->Channel, Request->Shape, Request->Params, Request->ResponseParam, &OverlapDelegate));
		// AsyncOverlapByObjectType
		else
		if (Request->Query == ECsTraceQuery::ObjectType)
			Request->CopyHandle(GetWorld()->AsyncOverlapByObjectType(Request->Start, Request->Rotation.Quaternion(), Request->ObjectParams, Request->Shape, Request->Params, &OverlapDelegate));
		// NOT SUPPORTED
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Sweep Trace %s By Profile Method. Use TraceQuery: Channel or ObjectType."), *TraceMethodAsString);
			Request->Reset();
			return false;
		}
	}
	return true;
}

#pragma endregion Request

// Response
#pragma region

FCsResource_TraceResponse* UCsManager_Trace::AllocateResponse()
{
	return Manager_Response.Allocate();
}

void UCsManager_Trace::OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum)
{
	const TCsTraceHandleId& HandleId = Handle._Handle;
	// Get Request
	FCsTraceRequest* Request = PendingRequestsByTraceHandle[HandleId];
	// Setup Response
	FCsTraceResponse* Response = AllocateResponse();

	Response->bResult	  = Datum.OutHits.Num() > CS_EMPTY && Datum.OutHits[CS_FIRST].bBlockingHit;
	Response->ElapsedTime = GetWorld()->GetTimeSeconds() - Request->StartTime;

	const uint8 Count = Datum.OutHits.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Response->OutHits.AddDefaulted();

		UCsLibrary_Common::CopyHitResult(Datum.OutHits[I], Response->OutHits[I]);
	}
	
#if !UE_BUILD_SHIPPING
	if (CsCVarDrawManagerTraceResponses->GetInt() == CS_CVAR_DRAW)
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

	// Broadcast Response
	Request->OnResponse_Event.Broadcast(Request->Id, Response);
	Response->Reset();

	Request->bProcessing = false;
	Request->bCompleted = true;
}

void UCsManager_Trace::OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum)
{
}

#pragma endregion Response

FCsResource_TraceResponse*  UCsManager_Trace::Trace(FCsResource_TraceRequest* Request)
{
	FCsTraceRequest* R = Request->Get();

	R->StartTime = GetWorld()->GetTimeSeconds();

	bool AddPending = !Request->bForce && ThisFrameCountInfo.TotalCount >= RequestsProcessedPerTick;

	// TODO: Print warning for a normal trace moved to Async
	if (AddPending && !Request->bAsync)
	{
		R->Reset();
		Manager_Request.Deallocate(Request);
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Trace::Trace: Reached maximum RequestsProcessedPerTick: %d and Request is NOT Async. Abandoning Request."), RequestsProcessedPerTick);
		return nullptr;
	}

	// Async
	if (R->bAsync ||
		AddPending)
	{
		// if NOT Pending, Start Async
		if (!AddPending)
		{
			// if Successful in processing Request, EXIT
			if (ProcessRequest(Request))
			{
				AddPendingRequest(Request);
				IncrementTraceCount(Request);
				return nullptr;
			}
		}

		// ADD Pending Request
		AddPendingRequest(Request);
		return nullptr;
	}
	// Normal
	else
	{
#if !UE_BUILD_SHIPPING
		if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
		{
			// Sphere around Start
			DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
		}
#endif // #if !UE_BUILD_SHIPPING

		FCsTraceResponse* Response = AllocateResponse();

		Response->ElapsedTime = GetWorld()->GetTimeSeconds() - Request->StartTime;

		// Line
		if (Request->Type == ECsTraceType::Line)
		{
			// Test
			if (Request->Method == ECsTraceMethod::Test)
			{
				// LineTraceTestByChannel
				if (Request->Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->LineTraceTestByChannel(Request->Start, Request->End, Request->Channel, Request->Params, Request->ResponseParam);
				// LineTraceTestByObjectType
				else
				if (Request->Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceTestByObjectType(Request->Start, Request->End, Request->ObjectParams, Request->Params);
				// LineTraceTestByProfile
				else
				if (Request->Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceTestByProfile(Request->Start, Request->End, Request->ProfileName, Request->Params);
			}
			// Single
			else
			if (Request->Method == ECsTraceMethod::Single)
			{
				Response->OutHits.AddDefaulted();

				// LineTraceSingleByChannel
				if (Request->Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->LineTraceSingleByChannel(Response->OutHits[CS_FIRST], Request->Start, Request->End, Request->Channel, Request->Params, Request->ResponseParam);
				// LineTraceSingleByObjectType
				else
				if (Request->Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceSingleByObjectType(Response->OutHits[CS_FIRST], Request->Start, Request->End, Request->ObjectParams, Request->Params);
				// LineTraceSingleByProfile
				else
				if (Request->Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceSingleByProfile(Response->OutHits[CS_FIRST], Request->Start, Request->End, Request->ProfileName, Request->Params);
			}
			// Multi
			else
			if (Request->Method == ECsTraceMethod::Multi)
			{
				// LineTraceMultiByChannel
				if (Request->Query == ECsTraceQuery::Channel)
					Response->bResult = GetWorld()->LineTraceMultiByChannel(Response->OutHits, Request->Start, Request->End, Request->Channel, Request->Params, Request->ResponseParam);
				// LineTraceMultiByObjectType
				else
				if (Request->Query == ECsTraceQuery::ObjectType)
					Response->bResult = GetWorld()->LineTraceMultiByObjectType(Response->OutHits, Request->Start, Request->End, Request->ObjectParams, Request->Params);
				// LineTraceMultiByProfile
				else
				if (Request->Query == ECsTraceQuery::Profile)
					Response->bResult = GetWorld()->LineTraceMultiByProfile(Response->OutHits, Request->Start, Request->End, Request->ProfileName, Request->Params);
			}
		}
		// Sweep
		else
		if (Request->Type == ECsTraceType::Sweep)
		{
			// Test
			if (Request->Method == ECsTraceMethod::Test)
			{
			}
			// Single
			else
			if (Request->Method == ECsTraceMethod::Single)
			{
				Response->OutHits.AddDefaulted();
			}
			// Multi
			else
			if (Request->Method == ECsTraceMethod::Multi)
			{
			}
		}
		// Overlap
		else
		if (Request->Type == ECsTraceType::Overlap)
		{
		}
		/*
		bool SweepTestByChannel(const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool SweepTestByObjectType(const FVector& Start, const FVector& End, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool SweepTestByProfile(const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params) const;
		bool SweepSingleByChannel(struct FHitResult& OutHit, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool SweepSingleByObjectType(struct FHitResult& OutHit, const FVector& Start, const FVector& End, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool SweepSingleByProfile(struct FHitResult& OutHit, const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool SweepMultiByChannel(TArray<struct FHitResult>& OutHits, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool SweepMultiByObjectType(TArray<struct FHitResult>& OutHits, const FVector& Start, const FVector& End, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool SweepMultiByProfile(TArray<FHitResult>& OutHits, const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool OverlapBlockingTestByChannel(const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool OverlapAnyTestByChannel(const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool OverlapAnyTestByObjectType(const FVector& Pos, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool OverlapBlockingTestByProfile(const FVector& Pos, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool OverlapAnyTestByProfile(const FVector& Pos, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool OverlapMultiByChannel(TArray<struct FOverlapResult>& OutOverlaps, const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;
		bool OverlapMultiByObjectType(TArray<struct FOverlapResult>& OutOverlaps, const FVector& Pos, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		bool OverlapMultiByProfile(TArray<struct FOverlapResult>& OutOverlaps, const FVector& Pos, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam) const;
		*/
		IncrementTraceCount(Request);
		Request->Reset();

#if !UE_BUILD_SHIPPING
		if (CsCVarDrawManagerTraceResponses->GetInt() == CS_CVAR_DRAW)
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
		return Response;
	}
	Request->Reset();
	return nullptr;
}

void ACsManager_Trace::LogTransaction(const FString& FunctionName, const ECsTraceTransaction& Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response)
{
#if !UE_BUILD_SHIPPING
	if (CsCVarLogManagerTraceTransactions->GetInt() == CS_CVAR_SHOW_LOG)
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
#endif // #if !UE_BUILD_SHIPPING
}