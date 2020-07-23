// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "WorldCollision.h"

#include "CsTypes_Trace.generated.h"
#pragma once

// TraceType
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsTraceType : uint8
{
	Line				UMETA(DisplayName = "Line"),
	Sweep				UMETA(DisplayName = "Sweep"),
	Overlap				UMETA(DisplayName = "Overlap"),
	ECsTraceType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceType : public TCsEnumMap<ECsTraceType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceType, ECsTraceType)
};

namespace NCsTraceType
{
	typedef ECsTraceType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Line;
		extern CSCORE_API const Type Sweep;
		extern CSCORE_API const Type Overlap;
		extern CSCORE_API const Type ECsTraceType_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_TYPE_MAX NCsTraceType::MAX

#pragma endregion TraceType

// TraceMethod
#pragma region TraceMethod

/**
*/
UENUM(BlueprintType)
enum class ECsTraceMethod : uint8
{
	Test				UMETA(DisplayName = "Test"),
	Single				UMETA(DisplayName = "Single"),
	Multi				UMETA(DisplayName = "Multi"),
	ECsTraceMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceMethod : public TCsEnumMap<ECsTraceMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceMethod, ECsTraceMethod)
};

namespace NCsTraceMethod
{
	typedef ECsTraceMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Test;
		extern CSCORE_API const Type Single;
		extern CSCORE_API const Type Multi;
		extern CSCORE_API const Type ECsTraceMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_METHOD_MAX NCsTraceMethod::MAX

#pragma endregion TraceMethod

// TraceQuery
#pragma region

UENUM(BlueprintType)
enum class ECsTraceQuery : uint8
{
	Channel				UMETA(DisplayName = "Channel"),
	ObjectType			UMETA(DisplayName = "ObjectType"),
	Profile				UMETA(DisplayName = "Profile"),
	ECsTraceQuery_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceQuery : public TCsEnumMap<ECsTraceQuery>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceQuery, ECsTraceQuery)
};

namespace NCsTraceQuery
{
	typedef ECsTraceQuery Type;

	namespace Ref
	{
		extern CSCORE_API const Type Channel;
		extern CSCORE_API const Type ObjectType;
		extern CSCORE_API const Type Profile;
		extern CSCORE_API const Type ECsTraceQuery_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_QUERY_MAX NCsTraceQuery::MAX

#pragma endregion TraceQuery

// TraceTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsTraceTransaction : uint8
{
	Add						UMETA(DisplayName = "Add"),
	Complete				UMETA(DisplayName = "Complete"),
	ECsTraceTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceTransaction : public TCsEnumMap<ECsTraceTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceTransaction, ECsTraceTransaction)
};

namespace NCsTraceTransaction
{
	typedef ECsTraceTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsTraceTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Add;
		extern CSCORE_API const TCsString Complete;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Complete) { return Str::Complete.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#define ECS_TRACE_TRANSACTION_MAX NCsTraceTransaction::MAX

#pragma endregion TraceTransaction

USTRUCT(BlueprintType)
struct CSCORE_API FCsTraceResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool bAllocated;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool bResult;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	float ElapsedTime;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	TArray<struct FHitResult> OutHits;

	TArray<struct FOverlapResult> OutOverlaps;

	FCsTraceResponse() 
	{
		Reset();
	}

	~FCsTraceResponse() 
	{
	}

	FORCEINLINE FCsTraceResponse& operator=(const FCsTraceResponse& B)
	{
		bAllocated = B.bAllocated;
		bResult = B.bResult;

		OutHits.Reset();

		for (const FHitResult& Hit : B.OutHits)
		{
			OutHits.Add(Hit);
		}

		for (const FOverlapResult& Overlap : B.OutOverlaps)
		{
			OutOverlaps.Add(Overlap);
		}
		ElapsedTime = B.ElapsedTime;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTraceResponse& B) const
	{
		if (bAllocated != B.bAllocated)
			return false;
		if (bResult != B.bResult)
			return false;
		if (ElapsedTime != B.ElapsedTime)
			return false;
		if (OutHits.Num() != B.OutHits.Num())
			return false;
		if (OutOverlaps.Num() != B.OutOverlaps.Num())
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsTraceResponse& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		bAllocated = false;
		bResult = false;
		ElapsedTime = 0.0f;

		OutHits.Reset();
		OutOverlaps.Reset();
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerTrace_OnResponse, const uint8&, RequestId, const FCsTraceResponse&, Response);

#define CS_INVALID_TRACE_REQUEST_ID 255

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

	UPROPERTY(BlueprintAssignable, Category = "Trace")
	FBindableDynEvent_CsManagerTrace_OnResponse OnRespone_ScriptEvent;

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
	~FCsTraceRequest() {}

	FORCEINLINE FCsTraceRequest& operator=(const FCsTraceRequest& B)
	{
		StaleTime = B.StaleTime;
		bAsync = B.bAsync;
		Type = B.Type;
		Method = B.Method;
		Query = B.Query;
		Start = B.Start;
		End = B.End;
		Rotation = B.Rotation;
		Channel = B.Channel;
		ProfileName = B.ProfileName;
		Shape = B.Shape;
		Params = B.Params;
		ObjectParams = B.ObjectParams;
		ResponseParam = B.ResponseParam;
		ReplacePending = B.ReplacePending;
		PendingId = B.PendingId;
		CopyHandle_Internal(B.Handle, Handle);
		return *this;
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
#if WITH_EDITOR
		OnRespone_ScriptEvent.Clear();
#endif // #if WITH_EDITOR

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