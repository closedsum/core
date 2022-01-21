// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Trace/CsTypes_Trace.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Collision/CsTypes_Collision.h"
#include "WorldCollision.h"
// Trace
#include "Managers/Trace/CsTraceResponse.h"
// Log
#include "Utility/CsLog.h"

#include "CsTraceRequest.generated.h"
#pragma once

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsTraceRequest_OnResponse, const FCsTraceResponse&, Response);

class UObject;
struct FCsTraceResponse;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

class UCapsuleComponent;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTraceRequest
{
	GENERATED_USTRUCT_BODY()

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaleTime;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Caller;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCollisionShape Shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCollisionQueryParams Params;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCollisionObjectQueryParams ObjectParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCollisionResponseParams ResponseParams;

	UPROPERTY(BlueprintAssignable)
	FCsTraceRequest_OnResponse OnResponse_Event;

	UPROPERTY(BlueprintAssignable)
	FCsTraceRequest_OnResponse OnResponse_AsyncEvent;

	FCsTraceRequest() :
		StaleTime(1.0f),
		Caller(nullptr),
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
		Params(),
		ObjectParams(),
		ResponseParams(),
		OnResponse_Event(),
		OnResponse_AsyncEvent()
	{
	}

#define RequestType NCsTrace::NRequest::FRequest
	void CopyToRequestAsValue(RequestType* Request) const;
#undef RequestType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE void Reset()
	{
		StaleTime = 1.0f;
		Caller = nullptr;

		bAsync = false;
		Type = ECsTraceType::ECsTraceType_MAX;
		Method = ECsTraceMethod::ECsTraceMethod_MAX;
		Query = ECsTraceQuery::ECsTraceQuery_MAX;
		Start = FVector::ZeroVector;
		End = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		Channel = ECollisionChannel::ECC_MAX;
		ProfileName = NAME_None;
		Shape.Reset();
		Params.Reset();
		ObjectParams.Reset();
		ResponseParams.Reset();

		OnResponse_Event.Clear();
		OnResponse_AsyncEvent.Clear();
	}
};

class UObject;
class ICsUniqueObject;

// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsTrace
{
	namespace NRequest
	{
		struct CSCORE_API FRequest
		{
		public:

			int32 Index;

			/** */
			FTraceHandle Handle;

			/** */
			bool bForce;

			/** */
			bool bProcessing;

			/** */
			bool bCompleted;

			/** */
			float StartTime;

			/** */
			FCsDeltaTime ElapsedTime;

			/** */
			float StaleTime;

			/** */
			TWeakObjectPtr<UObject> Caller;

			/** */
			ICsUniqueObject* UniqueObject;

			/** */
			bool bAsync;

			/** */
			ECsTraceType Type;

			/** */
			ECsTraceMethod Method;

			/** */
			ECsTraceQuery Query;

			/** The start location of the trace. */
			FVector Start;

			/** The end location of the trace. */
			FVector End;

			/** */
			FRotator Rotation;

			/** */
			TEnumAsByte<ECollisionChannel> Channel;

			/** */
			FName ProfileName;

			FCollisionShape Shape;
			FCollisionQueryParams Params;
			FCollisionObjectQueryParams ObjectParams;
			FCollisionResponseParams ResponseParams;

		#define ResponseType NCsTrace::NResponse::FResponse

			/** */
			ResponseType* Response;
		

			/** */
			DECLARE_MULTICAST_DELEGATE_OneParam(FOnResponse, ResponseType*);

		#undef ResponseType

			/** */
			FOnResponse OnResponse_Event;
			FCsTraceRequest_OnResponse OnResponse_ScriptEvent;

			/** */
			FOnResponse OnResponse_AsyncEvent;
			FCsTraceRequest_OnResponse OnResponse_AsyncScriptEvent;

			FRequest() :
				Index(INDEX_NONE),
				Handle(),
				bForce(false),
				bProcessing(false),
				bCompleted(false),
				StartTime(0.0f),
				ElapsedTime(),
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
				ResponseParams(FCollisionResponseParams::DefaultResponseParam),
				Response(nullptr),
				OnResponse_Event(),
				OnResponse_ScriptEvent(),
				OnResponse_AsyncEvent(),
				OnResponse_AsyncScriptEvent()
			{
			}
	
			void SetIndex(const int32& InIndex) { Index = InIndex; }
			FORCEINLINE const int32& GetIndex() const { return Index; }

			FORCEINLINE bool IsValid() const
			{
				return Index > INDEX_NONE;
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

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

			void SetCaller(UObject* InCaller);

			UObject* GetCaller() const;

			void SetShape(UCapsuleComponent* Component);

			FORCEINLINE bool HasExpired() const
			{
				return StaleTime > 0.0f && ElapsedTime.Time > StaleTime;
			}

			void Update(const FCsDeltaTime& DeltaTime);

			FORCEINLINE void Reset()
			{
				ResetHandle(Handle);

				bForce = false;
				bProcessing = false;
				bCompleted = false;
				StartTime = 0.0f;
				ElapsedTime.Reset();
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
				//Params = FCollisionQueryParams::DefaultQueryParam;
				NCsCollisionQueryParams::Reset(Params);
				ObjectParams = FCollisionObjectQueryParams::DefaultObjectQueryParam;
				ResponseParams = FCollisionResponseParams::DefaultResponseParam;

				Response = nullptr;
				OnResponse_Event.Clear();
				OnResponse_ScriptEvent.Clear();
				OnResponse_AsyncEvent.Clear();
				OnResponse_AsyncScriptEvent.Clear();
			}
		};
	}
}