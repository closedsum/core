// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "Runtime/Engine/Public/WorldCollision.h"

#include "CsTypes_Trace.generated.h"
#pragma once

// Trace
#pragma region

UENUM(BlueprintType)
namespace ECsTraceType
{
	enum Type
	{
		Line				UMETA(DisplayName = "Line"),
		Sweep				UMETA(DisplayName = "Sweep"),
		Overlap				UMETA(DisplayName = "Overlap"),
		ECsTraceType_MAX	UMETA(Hidden),
	};
}

typedef ECsTraceType::Type TCsTraceType;
#define ECS_TRACE_TYPE_MAX (uint8)ECsTraceType::ECsTraceType_MAX

struct CSCORE_API EMCsTraceType : public TCsEnumMap<ECsTraceType::Type>
{
protected:
	EMCsTraceType() {}
	EMCsTraceType(const EMCsTraceType &) = delete;
	EMCsTraceType(EMCsTraceType &&) = delete;
public:
	~EMCsTraceType() {}
private:
	static EMCsTraceType* Instance;

public:
	static EMCsTraceType& Get();
};

namespace ECsTraceType
{
	namespace Ref
	{
		extern CSCORE_API const Type Line;
		extern CSCORE_API const Type Sweep;
		extern CSCORE_API const Type Overlap;
		extern CSCORE_API const Type ECsTraceType_MAX;
	}
}

UENUM(BlueprintType)
namespace ECsTraceMethod
{
	enum Type
	{
		Test				UMETA(DisplayName = "Test"),
		Single				UMETA(DisplayName = "Single"),
		Multi				UMETA(DisplayName = "Multi"),
		ECsTraceMethod_MAX	UMETA(Hidden),
	};
}

typedef ECsTraceMethod::Type TCsTraceMethod;
#define ECS_TRACE_METHOD_MAX (uint8)ECsTraceMethod::ECsTraceMethod_MAX

struct CSCORE_API EMCsTraceMethod : public TCsEnumMap<ECsTraceMethod::Type>
{
protected:
	EMCsTraceMethod() {}
	EMCsTraceMethod(const EMCsTraceMethod &) = delete;
	EMCsTraceMethod(EMCsTraceMethod &&) = delete;
public:
	~EMCsTraceMethod() {}
private:
	static EMCsTraceMethod* Instance;

public:
	static EMCsTraceMethod& Get();
};

namespace ECsTraceMethod
{
	namespace Str
	{
		extern CSCORE_API const Type Test;
		extern CSCORE_API const Type Single;
		extern CSCORE_API const Type Multi;
		extern CSCORE_API const Type ECsTraceMethod_MAX;
	}
}

UENUM(BlueprintType)
namespace ECsTraceQuery
{
	enum Type
	{
		Channel				UMETA(DisplayName = "Channel"),
		ObjectType			UMETA(DisplayName = "ObjectType"),
		Profile				UMETA(DisplayName = "Profile"),
		ECsTraceQuery_MAX	UMETA(Hidden),
	};
}

typedef ECsTraceQuery::Type TCsTraceQuery;
#define ECS_TRACE_QUERY_MAX (uint8)ECsTraceQuery::ECsTraceQuery_MAX

struct CSCORE_API EMCsTraceQuery : public TCsEnumMap<ECsTraceQuery::Type>
{
protected:
	EMCsTraceQuery() {}
	EMCsTraceQuery(const EMCsTraceQuery &) = delete;
	EMCsTraceQuery(EMCsTraceQuery &&) = delete;
public:
	~EMCsTraceQuery() {}
private:
	static EMCsTraceQuery* Instance;

public:
	static EMCsTraceQuery& Get();
};

namespace ECsTraceQuery
{
	namespace Ref
	{
		extern CSCORE_API const Type Channel;
		extern CSCORE_API const Type ObjectType;
		extern CSCORE_API const Type Profile;
		extern CSCORE_API const Type ECsTraceQuery_MAX;
	}
}

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
	bool IsAllocated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool bProcessing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace")
	bool Completed;

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
	TEnumAsByte<ECsTraceType::Type> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TEnumAsByte<ECsTraceMethod::Type> Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TEnumAsByte<ECsTraceQuery::Type> Query;

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
		return	IsAllocated == B.IsAllocated &&
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
		IsAllocated = false;
		bForce = false;
		bProcessing = false;
		Completed = false;
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

#pragma endregion Trace