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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish, const uint8&, MappingId);
// AimAt
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnBTTask_AimAtLocation_Start, const uint8&, MappingId, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnBTTask_AimAtActor_Start, const uint8&, MappingId, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_AimAt_Aborted, const uint8&, MappingId);
// Shoot
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Start, const uint8&, MappingId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Stop, const uint8&, MappingId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Aborted, const uint8&, MappingId);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	FECsAIState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	FECsAIState SpawnedState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	FECsAISetup CurrentSetup;

#pragma endregion Setup

// State
#pragma region
public:

	virtual void OnChange_Health(const float &Value) override;

#pragma endregion State

// View
#pragma region
public:

	virtual void PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response) override;

#pragma endregion View

// Game Events
#pragma region
public:

#pragma endregion Game Events

// Behavior Tree
#pragma region
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior Tree")
	AActor* MyTargetActor;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetTargetActor(AActor* Target);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior Tree")
	FVector MyTargetLocation;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetTargetLocation(const FVector &Target);

	// RotateToFaceBBEntry
#pragma region
public:

		// Start
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnBTTask_RotateToFaceBBEntry_Start, const uint8&, const float&, const float&);

	FOnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_ScriptEvent;
		// Finish
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_RotateToFaceBBEntry_Finish, const uint8&);

	FOnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_ScriptEvent;

#pragma endregion RotateToFaceBBEntry

	// LookAt
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void LookAtLocation(const FVector &Target, const float &BlendInTime, const float &LookTime);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void LookAtActor(AActor* Target, const FName &Bone, const float &BlendInTime, const float &LookTime);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StopLookAt(const float &BlendOutTime);

#pragma endregion LookAt

	// AimAt
#pragma region
public:

		// Location Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_AimAtLocation_Start, const uint8&, const FVector&);

	FOnBTTask_AimAtLocation_Start OnBTTask_AimAtLocation_Start_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAtLocation_Start OnBTTask_AimAtLocation_Start_ScriptEvent;

		// Actor Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_AimAtActor_Start, const uint8&, AActor*);

	FOnBTTask_AimAtActor_Start OnBTTask_AimAtActor_Start_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAtActor_Start OnBTTask_AimAtActor_Start_ScriptEvent;

		// Abort
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_AimAt_Aborted, const uint8&);

	FOnBTTask_AimAt_Aborted OnBTTask_AimAt_Aborted_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAt_Aborted OnBTTask_AimAt_Aborted_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void AimAtLocation(const FVector &Target);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void AimAtActor(AActor* Target, const FName &Bone);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StopAimAt();

#pragma endregion AimtAt

	// Shoot
#pragma region
public:

		// Start
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Shoot_Start, const uint8&);

	FOnBTTask_Shoot_Start OnBTTask_Shoot_Start_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Start OnBTTask_Shoot_Start_ScriptEvent;

		// Stop
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Shoot_Stop, const uint8&);

	FOnBTTask_Shoot_Stop OnBTTask_Shoot_Stop_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Stop OnBTTask_Shoot_Stop_ScriptEvent;

		// Abort
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Shoot_Aborted, const uint8&);

	FOnBTTask_Shoot_Aborted OnBTTask_Shoot_Aborted_Event;

	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Aborted OnBTTask_Shoot_Aborted_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StartShoot();
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StopShoot();

#pragma endregion Shoot

#pragma endregion Behavior Tree

// Sense
#pragma region
public:

#pragma endregion Sense
};