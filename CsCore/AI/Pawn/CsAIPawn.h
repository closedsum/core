// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "Types/CsTypes_AI.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Trace.h"
#include "CsAIPawn.generated.h"

// RotateToFaceBBEntry
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start, const uint8&, MappingId, const float&, AngleDelta, const float&, RotationRate);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start, const uint8&, const float&, const float&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish, const uint8&, MappingId);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish, const uint8&);

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

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnTick_HandleCVars(const float &DeltaSeconds);

// State
#pragma region
public:

	virtual void OnTick_Handle_HealthBar();

#pragma endregion State

// Behavior Tree
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_ScriptEvent;

	FBindableEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_ScriptEvent;

	FBindableEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_Event;

#pragma endregion Behavior Tree

// Player
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	float PlayerToMeDot;

	void CalculatePlayerToMeDot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float PlayerSeesBodyMinDot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "90.0", UIMax = "80.0"))
	float PlayerSeesBodyAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bPlayerSeesBody;

	UFUNCTION(BlueprintCallable, Category = "Player")
	virtual void SetPlayerSeesBody(const bool &Value);

	TCsBool_Ref bPlayerSeesBodyHandle;
	virtual void OnChange_bPlayerSeesBody(const bool &Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CheckPlayerSeesBodyInterval;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	float CheckPlayerSeesBodyStartTime;

	void CheckPlayerSeesBody();
	void CheckPlayerSeesBody_Response(FCsTraceResponse* Response);

#pragma endregion Player
};