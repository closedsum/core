// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "Types/CsTypes_AI.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsAIPawn.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry, const uint8&, MappingId, const float&, DeltaSeconds);

DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsAIPawn_OnHandleRespawnTimerFinished, const uint8&);

// Enums
#pragma region

namespace ECsAIPawnRoutine
{
	enum Type
	{
		HandleRespawnTimer_Internal,
		ECsAIPawnRoutine_MAX,
	};
}

namespace ECsAIPawnRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString HandleRespawnTimer_Internal = TCsString(TEXT("HandleRespawnTimer_Internal"), TEXT("handlerespawntimer_internal"), TEXT("handle respawn timer internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::HandleRespawnTimer_Internal) { return Str::HandleRespawnTimer_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::HandleRespawnTimer_Internal) { return Type::HandleRespawnTimer_Internal; }
		return Type::ECsAIPawnRoutine_MAX;
	}
}

#define ECS_AI_PAWN_ROUTINE_MAX (uint8)ECsAIPawnRoutine::ECsAIPawnRoutine_MAX
typedef ECsAIPawnRoutine::Type TCsAIPawnRoutine;

#pragma endregion Enums

USTRUCT(BlueprintType)
struct FCsAIPawnCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsAIPawn> Pawn;

	// TODO: LifeTime

	FCsAIPawnCache()
	{
		Reset();
	}

	~FCsAIPawnCache(){}

	void Set(const uint16 &InIndex, ACsAIPawn* InPawn)
	{
		Index = InIndex;
		Pawn  = InPawn;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Parent = InParent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;

		if (InObject && OnDeAllocate)
		{
			DelegateInvoker = (UObject*)InObject;
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.AddUObject(InObject, OnDeAllocate);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.AddUObject(InObject, OnDeAllocate);
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Parent = InParent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		Reset_Internal();

		Pawn.Reset();
		Pawn = nullptr;
	}

	ACsAIPawn* GetPawn() { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsAIPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	bool IsAllocated;

	TCsAIType Type;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AI")
	uint8 Type_Script;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	struct FCsAIPawnCache Cache;

	void Init(const int32 &Index, const TCsAIType &InType);

	virtual void OnCreatePool();
	virtual void OnPostCreatePool();

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	void Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	void Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame);

	virtual void Allocate_Internal(FCsAIPawnPayload* Payload);

	virtual void DeAllocate();

	virtual void OnTick_HandleCVars(const float &DeltaSeconds);

// State
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float RespawnTime;

	CS_COROUTINE_DECLARE(HandleRespawnTimer)

	virtual void OnHandleRespawnTimerFinished(const uint8 &MappingId);

	FBindableEvent_CsAIPawn_OnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

#pragma endregion State

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type) override;

#pragma endregion Routines
};