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
// PlayerSeesBody
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnPlayerSeesBody, const uint8&, MappingId, const bool, Value);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsAIPawn_OnPlayerSeesBody, const uint8&, const bool&);

// Enums
#pragma region

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsAISenseInfo_Player
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 PlayerMappingId;

// Me to Player

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSensePlayerBySight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector MeToPlayerDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToPlayerDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToPlayerDistanceSq;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector MeToPlayerDirXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToPlayerDot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float TraceMeToPlayerBodyStartTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 TraceRequestId_MeToPlayerBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float TraceMeToPlayerHeadStartTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 TraceRequestId_MeToPlayerHead;

// Player to Me

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float PlayerToMeDot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bPlayerSeesMe;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bPlayerSeesBody;

	TCsBool_Ref bPlayerSeesBodyHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float CheckPlayerSeesBodyStartTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bPlayerSeesHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastKnown_DistanceToPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector LastKnown_PlayerLocation;

	FCsAISenseInfo_Player()
	{

	}
	~FCsAISenseInfo_Player(){}
};

#pragma endregion Structs

USTRUCT(BlueprintType)
struct FCsAIPawnCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsAIPawn> Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsAIType Type;

	FCsAIPawnCache()
	{
		Reset();
	}

	~FCsAIPawnCache(){}

	void Set(const int32 &InIndex, ACsAIPawn* InPawn)
	{
		Index = InIndex;
		Pawn  = InPawn;
	}

	void Init(const int32& InActiveIndex, FCsAIPawnPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		ActiveIndex = InActiveIndex;
		Owner = Payload->Owner;
		Parent = Payload->Parent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Pawn.Reset();
		Pawn = nullptr;
	}

	FORCEINLINE ACsAIPawn* GetPawn() { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetPawn() { return Cast<T>(GetPawn()); }
};

UCLASS()
class CSCORE_API ACsAIPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	bool IsAllocated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	FECsAIType Type;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	struct FCsAIPawnCache Cache;

	void Init(const int32 &Index, const FECsAIType &InType);

	virtual void OnCreatePool();
	virtual void OnPostCreatePool();

	void Allocate(const int32 &ActiveIndex, FCsAIPawnPayload* Payload);

	virtual void Allocate_Internal(FCsAIPawnPayload* Payload);

	virtual void DeAllocate();

	virtual void OnTick_HandleCVars(const float &DeltaSeconds);

// Setup
#pragma region
public:

	FECsAIState CurrentState;
	FECsAIState SpawnedState;

	FECsAISetup CurrentSetup;

#pragma endregion Setup

// State
#pragma region
public:

	virtual void OnChange_Health(const float &Value) override;

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

// Sense
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float ViewDot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float ViewAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SenseRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float SenseRadiusSq;
	/** Minimum Z distance below or above capsule to start checks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SenseHeight;

#pragma endregion Sense
};