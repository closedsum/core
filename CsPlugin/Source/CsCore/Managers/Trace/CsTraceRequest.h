// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"

#include "WorldCollision.h"

#include "CsTraceRequest.generated.h"
#pragma once

#define CS_INVALID_TRACE_REQUEST_ID 255

struct FCsTraceResponse;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTraceRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	uint8 Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bAllocated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bProcessing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bCompleted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	float StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	float StaleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TWeakObjectPtr<UObject> Caller;

	uint64 CallerId;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnResponse, const uint8&, FCsTraceResponse*);

	FOnResponse OnResponse_Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool bAsync;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	ECsTraceType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	ECsTraceMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	ECsTraceQuery Query;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FVector Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FVector End;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TEnumAsByte<ECollisionChannel> Channel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FName ProfileName;

	FCollisionShape Shape;
	FCollisionQueryParams Params;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionResponseParams ResponseParam;

	bool ReplacePending;
	uint8 PendingId;

	FTraceHandle Handle;

	TLinkedList<FCsTraceRequest*> Link;

	FCsTraceRequest() :
		Id(0)
	{
		Link = TLinkedList<FCsTraceRequest*>(this);

		Reset();
	}

	FORCEINLINE bool operator==(const FCsTraceRequest& B) const
	{
		return	bAllocated == B.bAllocated &&
				StaleTime == B.StaleTime &&
				bAsync == B.bAsync &&
				Type == B.Type &&
				Method == B.Method &&
				Query == B.Query &&
				Start == B.Start &&
				End == B.End &&
				Rotation == B.Rotation &&
				Channel == B.Channel &&
				ProfileName == B.ProfileName;
	}

	FORCEINLINE bool operator!=(const FCsTraceRequest& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		bAllocated = false;
		bForce = false;
		bProcessing = false;
		bCompleted = false;
		StartTime = 0.0f;
		StaleTime = 1.0f;
		Caller.Reset();
		Caller = nullptr;
		CallerId = UINT64_MAX;

		OnResponse_Event.Clear();

		bAsync = false;
		Type = ECsTraceType::ECsTraceType_MAX;
		Method = ECsTraceMethod::ECsTraceMethod_MAX;
		Query = ECsTraceQuery::ECsTraceQuery_MAX;
		Start = FVector::ZeroVector;
		End = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		Channel = ECollisionChannel::ECC_MAX;
		ProfileName = NAME_None;
		Shape.ShapeType = ECollisionShape::Line;
		Params = FCollisionQueryParams::DefaultQueryParam;
		ObjectParams = FCollisionObjectQueryParams::DefaultObjectQueryParam;
		ResponseParam = FCollisionResponseParams::DefaultResponseParam;
		ReplacePending = false;
		PendingId = CS_INVALID_TRACE_REQUEST_ID;

		ResetHandle(Handle);

		Link.Unlink();
	}

	FORCEINLINE void CopyHandle_Internal(const FTraceHandle &From, FTraceHandle &To)
	{
		To._Handle			 = From._Handle;
		To._Data.FrameNumber = From._Data.FrameNumber;
		To._Data.Index		 = From._Data.Index;
	}

	FORCEINLINE void CopyHandle(const FTraceHandle &InHandle)
	{
		CopyHandle_Internal(InHandle, Handle);
	}

	FORCEINLINE void ResetHandle(FTraceHandle &InHandle)
	{
		InHandle._Handle		   = 0;
		InHandle._Data.FrameNumber = 0;
		InHandle._Data.Index	   = 0;
	}
};