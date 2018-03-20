// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Pool.h"
//#include "Types/CsTypes_Item.h"
//#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "CsManager_Trace.generated.h"

// Enums
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

namespace ECsTraceType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Line = TCsString(TEXT("Line"), TEXT("line"));
		const TCsString Sweep = TCsString(TEXT("Sweep"), TEXT("sweep"));
		const TCsString Overlap = TCsString(TEXT("Overlap"), TEXT("overlap"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Line) { return Str::Line.Value; }
		if (EType == Type::Sweep) { return Str::Sweep.Value; }
		if (EType == Type::Overlap) { return Str::Overlap.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Line) { return Type::Line; }
		if (String == Str::Sweep) { return Type::Sweep; }
		if (String == Str::Overlap) { return Type::Overlap; }
		return Type::ECsTraceType_MAX;
	}
}

#define ECS_TRACE_TYPE_MAX (uint8)ECsTraceType::ECsTraceType_MAX
typedef ECsTraceType::Type TCsTraceType;

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

namespace ECsTraceMethod
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Test = TCsString(TEXT("Test"), TEXT("test"));
		const TCsString Single = TCsString(TEXT("Single"), TEXT("single"));
		const TCsString Multi = TCsString(TEXT("Multi"), TEXT("multi"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Test) { return Str::Test.Value; }
		if (EType == Type::Single) { return Str::Single.Value; }
		if (EType == Type::Multi) { return Str::Multi.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Test) { return Type::Test; }
		if (String == Str::Single) { return Type::Single; }
		if (String == Str::Multi) { return Type::Multi; }
		return Type::ECsTraceMethod_MAX;
	}
}

#define ECS_TRACE_METHOD_MAX (uint8)ECsTraceMethod::ECsTraceMethod_MAX
typedef ECsTraceMethod::Type TCsTraceMethod;

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

namespace ECsTraceQuery
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Channel = TCsString(TEXT("Channel"), TEXT("channel"));
		const TCsString ObjectType = TCsString(TEXT("ObjectType"), TEXT("objecttype"));
		const TCsString Profile = TCsString(TEXT("Profile"), TEXT("profile"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Channel) { return Str::Channel.Value; }
		if (EType == Type::ObjectType) { return Str::ObjectType.Value; }
		if (EType == Type::Profile) { return Str::Profile.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Channel) { return Type::Channel; }
		if (String == Str::ObjectType) { return Type::ObjectType; }
		if (String == Str::Profile) { return Type::Profile; }
		return Type::ECsTraceQuery_MAX;
	}
}

#define ECS_TRACE_QUERY_MAX (uint8)ECsTraceQuery::ECsTraceQuery_MAX
typedef ECsTraceQuery::Type TCsTraceQuery;

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsTraceResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool IsAllocated;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool bResult;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	float ElapsedTime;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	TArray<struct FHitResult> OutHits;

	TArray<struct FOverlapResult> OutOverlaps;

	~FCsTraceResponse() {}

	FCsTraceResponse() {}
	FCsTraceResponse& operator=(const FCsTraceResponse& B)
	{
		IsAllocated = B.IsAllocated;
		bResult = B.bResult;

		OutHits.Reset();

		const int32 HitCount = B.OutHits.Num();

		for (int32 I = 0; I < HitCount; ++I)
		{
			OutHits.Add(B.OutHits[I]);
		}

		OutOverlaps.Reset();

		const int32 OverlapCount = B.OutOverlaps.Num();

		for (int32 I = 0; I < OverlapCount; ++I)
		{
			OutOverlaps.Add(B.OutOverlaps[I]);
		}
		ElapsedTime = B.ElapsedTime;
		return *this;
	}

	bool operator==(const FCsTraceResponse& B) const
	{
		if (IsAllocated != B.IsAllocated)
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

	bool operator!=(const FCsTraceResponse& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		IsAllocated = false;
		bResult = false;
		ElapsedTime = 0.0f;

		OutHits.Reset();
		OutOverlaps.Reset();
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerTrace_OnResponse, const FCsTraceResponse&, Response);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerTrace_OnResponse, FCsTraceResponse*);

USTRUCT(BlueprintType)
struct FCsTraceRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	uint8 Id;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool IsAllocated;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool bProcessing;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	float StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	float StaleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TWeakObjectPtr<UObject> Caller;

	uint64 CallerId;

	UPROPERTY(BlueprintAssignable, Category = "Trace")
	FBindableDynEvent_CsManagerTrace_OnResponse OnRespone_ScriptEvent;

	FBindableEvent_CsManagerTrace_OnResponse OnResponse_Event;

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

	FTraceHandle Handle;

	FCsTraceRequest()
	{
		Reset();
	}
	~FCsTraceRequest(){}

	FCsTraceRequest& operator=(const FCsTraceRequest& B)
	{
		IsAllocated = B.IsAllocated;
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
		return *this;
	}

	bool operator==(const FCsTraceRequest& B) const
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

	bool operator!=(const FCsTraceRequest& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		bProcessing = false;
		IsAllocated = false;
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

		ResetHandle();
	}

	void CopyHandle(const FTraceHandle &InHandle)
	{
		Handle._Handle			 = InHandle._Handle;
		Handle._Data.FrameNumber = InHandle._Data.FrameNumber;
		Handle._Data.Index		 = InHandle._Data.Index;
	}

	void ResetHandle()
	{
		Handle._Handle			 = 0;
		Handle._Data.FrameNumber = 0;
		Handle._Data.Index		 = 0;
	}
};

#pragma endregion Structs

#define CS_POOLED_TRACE_REQUEST_SIZE 256
#define CS_POOLED_TRACE_RESPONSE_SIZE 256

// For Clarity
typedef uint64 TCsTraceHandleId;
typedef uint64 TCsObjectId;

UCLASS()
class CSCORE_API ACsManager_Trace : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Clear();
	virtual void Shutdown();
	virtual void BeginDestroy() override;

	static ACsManager_Trace* Get(UWorld* InWorld);

	virtual void OnTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	int32 RequestsProcessedPerTick;

	uint64 TraceCountLifetime;

	TMap<uint64, uint64> TraceCountLifetimeById;
	uint64 TraceCountLifetimeByType[ECS_TRACE_TYPE_MAX];
	uint64 TraceCountLifetimeByMethod[ECS_TRACE_METHOD_MAX];
	uint64 TraceCountLifetimeByQuery[ECS_TRACE_QUERY_MAX];

	uint16 TraceCountThisFrame;

	TMap<uint64, uint16> TraceCountThisFrameById;
	uint16 TraceCountThisFrameByType[ECS_TRACE_TYPE_MAX];
	uint16 TraceCountThisFrameByMethod[ECS_TRACE_METHOD_MAX];
	uint16 TraceCountThisFrameByQuery[ECS_TRACE_QUERY_MAX];

private:

	void IncrementTraceCount(FCsTraceRequest* Request);

// Request
#pragma region
private:

	FCsTraceRequest Requests[CS_POOLED_TRACE_REQUEST_SIZE];

	uint8 RequestIndex;

public:

	FCsTraceRequest* AllocateRequest();

	TMap<TCsTraceHandleId, FCsTraceRequest*> PendingRequests;
	TMap<TCsObjectId, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsById;
	TMap<TCsTraceType, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByType;
	TMap<TCsTraceMethod, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByMethod;
	TMap<TCsTraceQuery, TMap<TCsTraceHandleId, FCsTraceRequest*>> PendingRequestsByQuery;

private:

	void AddPendingRequest(FCsTraceRequest* Request);
	void RemovePendingRequest(FCsTraceRequest* Request);
	bool ProcessRequest(FCsTraceRequest* Request);

#pragma endregion Request

// Response
#pragma region
private:

	FCsTraceResponse Responses[CS_POOLED_TRACE_RESPONSE_SIZE];

	uint8 ResponseIndex;

public:

	FCsTraceResponse * AllocateResponse();

	FTraceDelegate TraceDelegate;
	FOverlapDelegate OverlapDelegate;

	void OnTraceResponse(const FTraceHandle& Handle, FTraceDatum& Datum);
	void OnOverlapResponse(const FTraceHandle& Handle, FOverlapDatum& Datum);

#pragma endregion Response

public:

	FCsTraceResponse* Trace(FCsTraceRequest* Request);

	/*
	UPROPERTY()
	uint64 UniqueIdIndex;

	TArray<uint64> AvailableUnqiueIds;

	virtual uint64 GetUniqueId();

	FCsItem Pool[CS_ITEM_POOL_SIZE];

	uint16 PoolIndex;
	*/
	//void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, const FCsItem* const Item);

private:

	//FCsItem* Allocate_Internal();

public:
	/*
	virtual FCsItem* Allocate();
	virtual FCsItem* Allocate(const FName &ShortCode);

	virtual void SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual FCsItem* Allocate(const FName &ShortCode, UObject* ItemOwner);

	TMap<uint64, FCsItem*> ActiveItems;
	TMap<uint64, TArray<FCsItem*>> ActiveItemsByOwnerId;

	void AddActiveItemByOwnerId(FCsItem* Item);

	void ChangeActiveItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual void SetActiveItemData(FCsItem* Item);
	*/
// Get
#pragma region
public:

	//virtual FCsItem* GetItem(const uint64 &Id);

	//void GetItemsByOwnerType(const TCsItemOwner &OwnerTyper, TArray<FCsItem*> &OutItems);
	//void GetItemsByOwnerId(const uint64 &OwnerId, TArray<FCsItem*> &OutItems);

#pragma endregion Get

// DeAllocate
#pragma region
public:

	//virtual void DeAllocate(const uint64 &Id);
	//virtual void DeAllocate(FCsItem* Item);

#pragma endregion DeAllocate
};