// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Trace/CsTypes_Trace.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Collision/CsTypes_Collision.h"
#include "WorldCollision.h"
// Trace
#include "Managers/Trace/CsTraceResponse.h"
// Log
#include "Utility/CsPhysicsLog.h"

#include "CsTraceRequest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsTraceRequest_OnResponse, const FCsTraceResponse&, Response);

class UObject;
struct FCsTraceResponse;

// RequestType (NCsTrace::NRequest::FRequest)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

class UCapsuleComponent;

/**
*/
USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsTraceRequest
{
	GENERATED_USTRUCT_BODY()

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	float StaleTime;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	UObject* Caller;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	bool bAsync;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	ECsTraceType Type;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	ECsTraceMethod Method;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	ECsTraceQuery Query;

	/** The start location of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FVector Start;

	/** The end location of the trace. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FVector End;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FRotator Rotation;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	TEnumAsByte<ECollisionChannel> Channel;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FName ProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FCsCollisionShape Shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FCsCollisionQueryParams Params;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FCsCollisionObjectQueryParams ObjectParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace")
	FCsCollisionResponseParams ResponseParams;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Trace")
	FCsTraceRequest_OnResponse OnResponse_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Trace")
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

	using RequestType = NCsTrace::NRequest::FRequest;

	void CopyToRequestAsValue(RequestType* Request) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsPhysics::FLog::Warning) const;

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

// ResponseType (NCsTrace::NResponse::FResponse)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsTrace
{
	namespace NRequest
	{
		struct CSPHYSICS_API FRequest
		{
		private:

			using ResponseType = NCsTrace::NResponse::FResponse;
			
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

			/** */
			ResponseType* Response;
		

			/** */
			DECLARE_MULTICAST_DELEGATE_OneParam(FOnResponse, ResponseType*);

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
				bAsync(false),
				Type(ECsTraceType::ECsTraceType_MAX),
				Method(ECsTraceMethod::ECsTraceMethod_MAX),
				Query(ECsTraceQuery::ECsTraceQuery_MAX),
				Start(FVector3f::ZeroVector),
				End(FVector3f::ZeroVector),
				Rotation(FRotator3f::ZeroRotator),
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
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsPhysics::FLog::Warning) const;

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

			void SetShape(const UCapsuleComponent* Component);

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

using CsTraceRequestType = NCsTrace::NRequest::FRequest;