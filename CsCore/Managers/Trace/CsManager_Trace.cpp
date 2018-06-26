// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsManager_Trace.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

// Cache
#pragma region

namespace ECsManagerTraceCached
{
	namespace Str
	{
		const FString Trace = TEXT("ACsManager_Trace::Trace");
		const FString ProcessRequest = TEXT("ACsManager_Trace::ProcessRequest");
		const FString OnTraceResponse = TEXT("ACsManager_Trace::OnTraceResponse");
	}
}

#pragma endregion Cache

ACsManager_Trace::ACsManager_Trace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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
		PendingRequestsByType.Add((TCsTraceType)I, AddMap);
	}

	for (uint8 I = 0; I < ECS_TRACE_METHOD_MAX; ++I)
	{
		TraceCountLifetimeByMethod[I] = 0;
		TraceCountThisFrameByMethod[I] = 0;

		TMap<TCsTraceRequestId, FCsTraceRequest*> AddMap;
		PendingRequestsByMethod.Add((TCsTraceMethod)I, AddMap);
	}

	for (uint8 I = 0; I < ECS_TRACE_QUERY_MAX; ++I)
	{
		TraceCountLifetimeByQuery[I] = 0;
		TraceCountThisFrameByQuery[I] = 0;

		TMap<TCsTraceRequestId, FCsTraceRequest*> AddMap;
		PendingRequestsByQuery.Add((TCsTraceQuery)I, AddMap);
	}

	TraceDelegate.BindUObject(this, &ACsManager_Trace::OnTraceResponse);
	OverlapDelegate.BindUObject(this, &ACsManager_Trace::OnOverlapResponse);
}

void ACsManager_Trace::Clear()
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

void ACsManager_Trace::Shutdown()
{
	Clear();
}

void ACsManager_Trace::BeginDestroy()
{
	Shutdown();
	Super::BeginDestroy();
}

/*static*/ ACsManager_Trace* ACsManager_Trace::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Trace;
}

void ACsManager_Trace::OnTick(const float &DeltaSeconds)
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

	//TLinkedList<FCsTraceRequest*>& PendingRequestQueue = *PendingRequestHead;

	TLinkedList<FCsTraceRequest*>* Current = PendingRequestHead;

	while (Current)
	{
		FCsTraceRequest* Request = **Current;
		Current					 = PendingRequestHead->GetNextLink();

		// If Processing, SKIP
		if (Request->bProcessing)
			continue;
		// If COMPLETED, Remove
		if (Request->Completed)
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

void ACsManager_Trace::IncrementTraceCount(FCsTraceRequest* Request)
{
	// Lifetime
	++TraceCountLifetime;

	if (uint64* CountById = TraceCountLifetimeByObjectId.Find(Request->CallerId))
	{
		++(*CountById);
	}
	else
	{
		TraceCountLifetimeByObjectId.Add(Request->CallerId, 1);
	}

	++(TraceCountLifetimeByType[(uint8)Request->Type]);
	++(TraceCountLifetimeByMethod[(uint8)Request->Method]);
	++(TraceCountLifetimeByQuery[(uint8)Request->Query]);
	// Frame
	++TraceCountThisFrame;

	if (uint16* CountById = TraceCountThisFrameByObjectId.Find(Request->CallerId))
	{
		++(*CountById);
	}
	else
	{
		TraceCountThisFrameByObjectId.Add(Request->CallerId, 1);
	}

	++(TraceCountThisFrameByType[(uint8)Request->Type]);
	++(TraceCountThisFrameByMethod[(uint8)Request->Method]);
	++(TraceCountThisFrameByQuery[(uint8)Request->Query]);
}

// Request
#pragma region

FCsTraceRequest* ACsManager_Trace::AllocateRequest()
{
	for (uint8 I = 0; I < CS_POOLED_TRACE_REQUEST_SIZE; ++I)
	{
		const uint8 Index		 = (RequestIndex + I) % CS_POOLED_TRACE_REQUEST_SIZE;
		FCsTraceRequest* Request = &(Requests[Index]);

		if (!Request->IsAllocated)
		{
			Request->IsAllocated = true;
			return Request;
		}
	}
	checkf(0, TEXT("ACsManager_Trace::AllocateRequest: Pool is exhausted"));
	return nullptr;
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
		PendingRequestsByTraceId.Add(HandleId, Request);
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

	PendingRequestsByTraceId.Remove(PendingHandleId);
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

	PendingRequestsByTraceId.Remove(HandleId);
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

bool ACsManager_Trace::ProcessRequest(FCsTraceRequest* Request)
{
	if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
	{
		// Sphere around Start
		DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
		// Line from Start to End
		DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
	}

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
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Line Trace %s By Profile Method. Use TraceMethod: Channel or ObjectType."), *TraceMethodAsString);
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
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Sweep Trace %s By Profile Method. Use TraceMethod: Channel or ObjectType."), *TraceMethodAsString);
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
		else
		if (Request->Query == ECsTraceQuery::Profile)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::ProcessRequest: There is NO Async Sweep Trace %s By Profile Method. Use TraceMethod: Channel or ObjectType."), *TraceMethodAsString);
			Request->Reset();
			return false;
		}
	}
	return true;
}

#pragma endregion Request

// Response
#pragma region

FCsTraceResponse* ACsManager_Trace::AllocateResponse()
{
	for (uint8 I = 0; I < CS_POOLED_TRACE_RESPONSE_SIZE; ++I)
	{
		const uint8 Index		   = (ResponseIndex + I) % CS_POOLED_TRACE_RESPONSE_SIZE;
		FCsTraceResponse* Response = &(Responses[Index]);

		if (!Response->IsAllocated)
		{
			Response->IsAllocated = true;
			return Response;
		}
	}
	checkf(0, TEXT("ACsManager_Trace::AllocateResponse: Pool is exhausted"));
	return nullptr;
}

void ACsManager_Trace::OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum)
{
	const TCsTraceHandleId& HandleId = Handle._Handle;
	// Get Request
	FCsTraceRequest* Request = PendingRequestsByTraceId[HandleId];
	// Setup Response
	FCsTraceResponse* Response = AllocateResponse();

	Response->bResult	  = Datum.OutHits.Num() > CS_EMPTY && Datum.OutHits[CS_FIRST].bBlockingHit;
	Response->ElapsedTime = GetWorld()->GetTimeSeconds() - Request->StartTime;

	const uint8 Count = Datum.OutHits.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Response->OutHits.AddDefaulted();

		UCsCommon::CopyHitResult(Datum.OutHits[I], Response->OutHits[I]);
	}
	
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

	LogTransaction(ECsManagerTraceCached::Str::OnTraceResponse, ECsTraceTransaction::Complete, Request, Response);

	// Broadcast Response
	Request->OnResponse_Event.Broadcast(Request->Id, Response);
	Response->Reset();

	Request->bProcessing = false;
	Request->Completed = true;
}

void ACsManager_Trace::OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum)
{
}

#pragma endregion Response

FCsTraceResponse*  ACsManager_Trace::Trace(FCsTraceRequest* Request)
{
	Request->StartTime = GetWorld()->GetTimeSeconds();

	bool AddPending = TraceCountThisFrame >= RequestsProcessedPerTick;

	// TODO: Print warning for a normal trace moved to Async
	if (AddPending && !Request->bAsync)
	{
		Request->Reset();
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Trace::Trace: Reached maximum RequestsProcessedPerTick: %d and Request is NOT Async. Abandoning Request."), RequestsProcessedPerTick);
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
		if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
		{
			// Sphere around Start
			DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
			// Line from Start to End
			DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
		}

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
		return Response;
	}
	Request->Reset();
	return nullptr;
}

void ACsManager_Trace::LogTransaction(const FString &FunctionName, const TCsTraceTransaction &Transaction, FCsTraceRequest* Request, FCsTraceResponse* Response)
{
	if (CsCVarLogManagerTraceTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		/*
		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = FString::Printf(TEXT("%llu"), Item->UniqueId);
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const ACsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : ECsCached::Str::Empty;
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