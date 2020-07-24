// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"

#include "WorldCollision.h"

#include "CsTraceRequest.generated.h"
#pragma once

class ICsUniqueObject;
struct FCsTraceResponse;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTraceRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Index;

	/** */
	FTraceHandle Handle;

	/** */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bForce;

	/** */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bProcessing;

	/** */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCompleted;

	/** */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StartTime;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaleTime;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<UObject> Caller;

	/** */
	ICsUniqueObject* UniqueObject;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAsync;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsTraceType Type;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsTraceMethod Method;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsTraceQuery Query;

	/** The start location of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Start;

	/** The end location of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector End;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> Channel;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ProfileName;

	FCollisionShape Shape;
	FCollisionQueryParams Params;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionResponseParams ResponseParam;

	/** */
	FCsTraceResponse* Response;

	/** */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnResponse, FCsTraceResponse*);

	/** */
	FOnResponse OnResponse_Event;

	/** */
	FOnResponse OnResponse_AsyncEvent;

	FCsTraceRequest() :
		Index(INDEX_NONE),
		Handle(),
		bForce(false),
		bProcessing(false),
		bCompleted(false),
		StartTime(0.0f),
		StaleTime(1.0f),
		Caller(nullptr),
		UniqueObject(nullptr),
		bAsync(false),
		Type(ECsTraceType::ECsTraceType_MAX),
		Method(ECsTraceMethod::ECsTraceMethod_MAX),
		Query(ECsTraceQuery::ECsTraceQuery_MAX),
		Start(FVector::ZeroVector),
		End(FVector::ZeroVector),
		Rotation(FRotator::ZeroRotator),
		Channel(ECollisionChannel::ECC_MAX),
		ProfileName(NAME_None),
		Shape(),
		Params(FCollisionQueryParams::DefaultQueryParam),
		ObjectParams(FCollisionObjectQueryParams::DefaultObjectQueryParam),
		ResponseParam(FCollisionResponseParams::DefaultResponseParam),
		Response(nullptr),
		OnResponse_Event(),
		OnResponse_AsyncEvent()
	{
	}
	
	void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE bool IsValid() const
	{
		return Index > INDEX_NONE;
	}

	FORCEINLINE bool IsHandleValid() const
	{
		return Handle._Handle != 0ull && Handle._Data.FrameNumber != 0 && Handle._Data.Index != 0;
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

	FORCEINLINE void Reset()
	{
		ResetHandle(Handle);

		bForce = false;
		bProcessing = false;
		bCompleted = false;
		StartTime = 0.0f;
		StaleTime = 1.0f;
		Caller = nullptr;
		UniqueObject = nullptr;

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

		Response = nullptr;
		OnResponse_Event.Clear();
		OnResponse_AsyncEvent.Clear();
	}
};