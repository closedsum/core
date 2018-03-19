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
	/*
	for (uint16 I = 0; I < CS_ITEM_POOL_SIZE; ++I)
	{
		Pool[I].Init(I);
	}

	UniqueIdIndex = CS_ITEM_UNIQUE_ID_START_INDEX;

	SaveDirectory = TEXT("Items/");
	*/
	RequestsProcessedPerTick = 64;

	for (uint8 I = 0; I < CS_POOLED_TRACE_REQUEST_SIZE; ++I)
	{
		Requests[I].Id = I;
	}
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

void ACsManager_Trace::OnResponse(const FTraceHandle& Handle, FTraceDatum& Datum)
{
}

#pragma endregion Response

FCsTraceResponse*  ACsManager_Trace::Trace(FCsTraceRequest* Request)
{
	bool AddPending = TraceCountThisFrame >= RequestsProcessedPerTick;

	// Async
	if (Request->bAsync ||
		AddPending)
	{
		// TODO: Print warning for a normal trace moved to Async
		if (AddPending && !Request->bAsync)
		{
			// Line
			if (Request->Type == ECsTraceType::Line)
			{
				// Test
				if (Request->Method == ECsTraceMethod::Test)
				{
					// TODO: Print Warning
				}
				// Single
				else
				if (Request->Method == ECsTraceMethod::Single)
				{
				}
				// Multi
				else
				if (Request->Method == ECsTraceMethod::Multi)
				{
					// TODO:: Print Warning
				}
			}
			/*
			FTraceHandle	AsyncLineTraceByChannel(EAsyncTraceType InTraceType, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, FTraceDelegate * InDelegate = NULL, uint32 UserData = 0);
			FTraceHandle	AsyncLineTraceByObjectType(EAsyncTraceType InTraceType, const FVector& Start, const FVector& End, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, FTraceDelegate * InDelegate = NULL, uint32 UserData = 0);
			FTraceHandle	AsyncSweepByChannel(EAsyncTraceType InTraceType, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, FTraceDelegate * InDelegate = NULL, uint32 UserData = 0);
			FTraceHandle	AsyncSweepByObjectType(EAsyncTraceType InTraceType, const FVector& Start, const FVector& End, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, FTraceDelegate * InDelegate = NULL, uint32 UserData = 0);
			FTraceHandle	AsyncOverlapByChannel(const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, FOverlapDelegate * InDelegate = NULL, uint32 UserData = 0);
			FTraceHandle	AsyncOverlapByObjectType(const FVector& Pos, const FQuat& Rot, const FCollisionObjectQueryParams& ObjectQueryParams, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, FOverlapDelegate * InDelegate = NULL, uint32 UserData = 0);
			*/
		}
	}
	else
	{
		FCsTraceResponse* Response = AllocateResponse();

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
		return Response;
	}
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