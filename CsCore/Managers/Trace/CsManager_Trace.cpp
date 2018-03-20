// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsManager_Trace.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

// Cache
#pragma region

namespace ECsManagerTraceCachedString
{
	namespace Str
	{
		const FString Allocate = TEXT("ACsManager_Trace::Allocate");
		const FString DeAllocate = TEXT("ACsManager_Trace::DeAllocate");
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
		TraceCountLifetimeByType.Add((TCsTraceType)I, 0);
		TraceCountThisFrameByType.Add((TCsTraceType)I, 0);

		TArray<FCsTraceRequest*> AddRequests;
		PendingRequestsByType.Add((TCsTraceType)I, AddRequests);
	}

	for (uint8 I = 0; I < ECS_TRACE_METHOD_MAX; ++I)
	{
		TraceCountLifetimeByMethod.Add((TCsTraceMethod)I, 0);
		TraceCountThisFrameByMethod.Add((TCsTraceMethod)I, 0);

		TArray<FCsTraceRequest*> AddRequests;
		PendingRequestsByMethod.Add((TCsTraceMethod)I, AddRequests);
	}

	for (uint8 I = 0; I < ECS_TRACE_QUERY_MAX; ++I)
	{
		TraceCountLifetimeByQuery.Add((TCsTraceQuery)I, 0);
		TraceCountThisFrameByQuery.Add((TCsTraceQuery)I, 0);

		TArray<FCsTraceRequest*> AddRequests;
		PendingRequestsByQuery.Add((TCsTraceQuery)I, AddRequests);
	}

	TraceDelegate.BindUObject(this, &ACsManager_Trace::OnTraceResponse);
	OverlapDelegate.BindUObject(this, &ACsManager_Trace::OnOverlapResponse);
}

void ACsManager_Trace::Clear()
{
	//Pool.Reset();
	//ActiveWidgets.Reset();
}

void ACsManager_Trace::Shutdown()
{
	/*
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->ConditionalBeginDestroy();
	}
	*/
	Clear();
}

void ACsManager_Trace::BeginDestroy()
{
	//Shutdown();
	Super::BeginDestroy();
}

/*static*/ ACsManager_Trace* ACsManager_Trace::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Trace;
}

void ACsManager_Trace::OnTick(const float &DeltaSeconds)
{
	const uint8 ProcessCountMax = FMath::Max(0, RequestsProcessedPerTick - TraceCountThisFrame);
	const uint8 Count			= (uint8)FMath::Min(PendingRequests.Num(), (int32)ProcessCountMax);

	for (uint8 I = 0; I < Count; ++I)
	{
		FCsTraceRequest* Request = PendingRequests[I];

		if (!Request->bProcessing)
			ProcessRequest(Request);
	}
}

void ACsManager_Trace::IncrementTraceCount(FCsTraceRequest* Request)
{
	++TraceCountLifetime;

	if (uint64* CountById = TraceCountLifetimeById.Find(Request->CallerId))
	{
		++(*CountById);
	}
	else
	{
		TraceCountLifetimeById.Add(Request->CallerId, 1);
	}

	uint64* LifetimeCountByType = TraceCountLifetimeByType.Find(Request->Type);
	++(*LifetimeCountByType);
	uint64* LifetimeCountByMethod = TraceCountLifetimeByMethod.Find(Request->Method);
	++(*LifetimeCountByMethod);
	uint64* LifetimeCountByQuery = TraceCountLifetimeByQuery.Find(Request->Query);
	++(*LifetimeCountByQuery);

	++TraceCountThisFrame;
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

bool ACsManager_Trace::ProcessRequest(FCsTraceRequest* Request)
{
	Request->bProcessing = true;

	EAsyncTraceType AsyncTraceType	   = EAsyncTraceType::Single;
	const FString& TraceMethodAsString = ECsTraceMethod::ToString(Request->Method);

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
	IncrementTraceCount(Request);
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
			// if NOT Successful in processing Request, EXIT
			if (!ProcessRequest(Request))
				return nullptr;
		}

		// ADD Pending Request
		PendingRequests.Add(Request);

		if (TArray<FCsTraceRequest*>* Requests = PendingRequestsById.Find(Request->CallerId))
		{
			Requests->Add(Request);
		}
		else
		{
			TArray<FCsTraceRequest*> NewRequests;
			NewRequests.Add(Request);
			PendingRequestsById.Add(Request->CallerId, NewRequests);
		}

		TArray<FCsTraceRequest*>* RequestsType = PendingRequestsByType.Find(Request->Type);
		RequestsType->Add(Request);
		TArray<FCsTraceRequest*>* RequestsMethod = PendingRequestsByMethod.Find(Request->Method);
		RequestsMethod->Add(Request);
		TArray<FCsTraceRequest*>* RequestsQuery = PendingRequestsByQuery.Find(Request->Query);
		RequestsQuery->Add(Request);
	}
	// Normal
	else
	{
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
		return Response;
	}
	Request->Reset();
	return nullptr;
}

/*
void ACsManager_Item::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, const FCsItem* const Item)
{
	if (CsCVarLogManagerItemTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = FString::Printf(TEXT("%llu"), Item->UniqueId);
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const ACsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : ECsCachedString::Str::Empty;
		const float CurrentTime				  = GetWorld()->GetTimeSeconds();

		if (Data_Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: %s, Data: %s, and with Data_Actor: %s at %f."), *FunctionName, *TransactionAsString, *ItemName,*Id, *DataName, *DataActorName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: % and Data: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *Id, *DataName, CurrentTime);
		}
	}
}
*/