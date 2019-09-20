// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "Types/CsTypes_AI.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Trace.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsAIPawn.generated.h"

// Jump
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_Jump_Start, const uint8&, MappingId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_Jump_Finish, const uint8&, MappingId);
// RotateToFaceBBEntry
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start, const uint8&, MappingId, const float&, AngleDelta, const float&, RotationRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish, const uint8&, MappingId);
// LookAtAndRotateToFace
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsAIPawn_OnBTTask_LookAtAndRotateToFace_Start, const uint8&, MappingId, const float&, AngleDelta, const float&, RotationRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_LookAtAndRotateToFace_Finish, const uint8&, MappingId);
// LookAt
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnBTTask_LookAtLocation_Start, const uint8&, MappingId, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_OnBTTask_LookAtActor_Start, const uint8&, MappingId, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsAIPawn_OnBTTask_LookAt_Aborted, const uint8&, MappingId);
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

namespace ECsPawnRoutine
{
	extern CSCORE_API const FECsPawnRoutine StartShootForCount_Internal;
	extern CSCORE_API const FECsPawnRoutine StartShootForDuration_Internal;
	extern CSCORE_API const FECsPawnRoutine SyncCurrentViewFromBone_Internal;
}

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsAIPawnCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsAIPawn> Pawn;

	UPROPERTY(BlueprintReadWrite, Category = "Cache")
	FECsAIType Type;

	FCsAIPawnCache()
	{
		Reset();
	}

	~FCsAIPawnCache(){}

	void Set(const int32 &InIndex, ACsAIPawn* InPawn, const FECsAIType &InType)
	{
		Index = InIndex;
		Pawn  = InPawn;
		Type  = InType;
	}

	void Init(FCsAIPawnPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Owner = Payload->Owner;
		Parent = Payload->Parent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	virtual void Reset() override
	{
		Super::Reset();

		Pawn.Reset();
		Pawn = nullptr;
	}

	FORCEINLINE ACsAIPawn* GetPawn() { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetPawn() { return Cast<T>(GetPawn()); }
};

USTRUCT(BlueprintType)
struct FCsAIPawnJumpEventInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FECsGameEvent Event;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector Direction;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float JumpZVelocity;


	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;
	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Height;
	UPROPERTY(BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SpeedXYAsPercent;

	FCsAIPawnJumpEventInfo() 
	{
		Event = EMCsGameEvent::Get().GetMAX();

		Clear();
	}
	~FCsAIPawnJumpEventInfo() {}

	void Clear()
	{
		Direction = FVector::ZeroVector;
		JumpZVelocity = 0.0f;

		Time = 0.0f;
		Height = 0.0f;

		SpeedXYAsPercent = 1.0f;
	}
};

#pragma endregion Structs

UCLASS()
class CSCORE_API ACsAIPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	struct FCsAIPawnCache Cache;

	void Init(const int32 &Index, const FECsAIType &InType);

	virtual void OnCreatePool();
	virtual void OnPostCreatePool();

	void Allocate(FCsAIPawnPayload* Payload);

	virtual void Allocate_Internal(FCsAIPawnPayload* Payload);

	virtual void DeAllocate();

	virtual void OnTick_HandleCVars(const float &DeltaSeconds);

// Setup
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FECsAIState CurrentState;
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FECsAIState SpawnedState;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FECsAISetup CurrentSetup;

#pragma endregion Setup

// State
#pragma region
public:

	virtual void OnChange_Health(const float &Value) override;

#pragma endregion State

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;

#pragma endregion Routines

// View
#pragma region
public:

	virtual void PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response) override;

	UPROPERTY(BlueprintReadOnly, Category = "View")
	bool bSyncCurrentViewFromBone;

	virtual void SyncCurrentViewFromBone(const FName &Bone);
	static char SyncCurrentViewFromBone_Internal(FCsRoutine* r);
	FCsRoutine* SyncCurrentViewFromBone_Internal_Routine;

	virtual void StopSyncCurrentViewFromBone();

#pragma endregion View

// Game Events
#pragma region
public:

#pragma endregion Game Events

// Behavior Tree
#pragma region
public:

	// Jump
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Behavior Tree")
	FCsAIPawnJumpEventInfo StartJumpEventInfo;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetStartJumpEventInfoConstrainedByTime(const FVector &Direction, const float &Distance);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetStartJumpEventInfoConstrainedBySpeedXY(const FVector &Direction, const float &Distance);

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetStartJumpEventInfo(const FVector &Direction, const float &SpeedXYAsPercent = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetStartJumpEventInfoByTime(const FVector &Direction, const float &Time, const float &SpeedXYAsPercent = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetStartJumpEventInfoByHeight(const FVector &Direction, const float &Height, const float &SpeedXYAsPercent = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StartJump();

	// Start
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Jump_Start, const uint8&);
	FOnBTTask_Jump_Start OnBTTask_Jump_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Jump_Start OnBTTask_Jump_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
	// Finish
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Jump_Finish, const uint8&);
	FOnBTTask_Jump_Finish OnBTTask_Jump_Finish_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Jump_Finish OnBTTask_Jump_Finish_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

#pragma endregion Jump

	UPROPERTY(BlueprintReadOnly, Category = "Behavior Tree")
	AActor* MyTargetActor;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetTargetActor(AActor* Target);

	UPROPERTY(BlueprintReadOnly, Category = "Behavior Tree")
	FVector MyTargetLocation;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void SetTargetLocation(const FVector &Target);

	// RotateToFaceBBEntry
#pragma region
public:

		// Start
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnBTTask_RotateToFaceBBEntry_Start, const uint8&, const float&, const float&);
	FOnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Start OnBTTask_RotateToFaceBBEntry_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Finish
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_RotateToFaceBBEntry_Finish, const uint8&);
	FOnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_RotateToFaceBBEntry_Finish OnBTTask_RotateToFaceBBEntry_Finish_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

#pragma endregion RotateToFaceBBEntry

	// LookAtAndRotateToFace
#pragma region
public:

		// Start
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnBTTask_LookAtAndRotateToFace_Start, const uint8&, const float&, const float&);
	FOnBTTask_LookAtAndRotateToFace_Start OnBTTask_LookAtAndRotateToFace_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_LookAtAndRotateToFace_Start OnBTTask_LookAtAndRotateToFace_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Finish
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_LookAtAndRotateToFace_Finish, const uint8&);
	FOnBTTask_LookAtAndRotateToFace_Finish OnBTTask_LookAtAndRotateToFace_Finish_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_LookAtAndRotateToFace_Finish OnBTTask_LookAtAndRotateToFace_Finish_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

#pragma endregion LookAtAndRotateToFace

	// LookAt
#pragma region
public:

		// Location Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_LookAtLocation_Start, const uint8&, const FVector&);
	FOnBTTask_LookAtLocation_Start OnBTTask_LookAtLocation_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_LookAtLocation_Start OnBTTask_LookAtLocation_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Actor Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_LookAtActor_Start, const uint8&, AActor*);
	FOnBTTask_LookAtActor_Start OnBTTask_LookAtActor_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_LookAtActor_Start OnBTTask_LookAtActor_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Abort
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_LookAt_Aborted, const uint8&);
	FOnBTTask_LookAt_Aborted OnBTTask_LookAt_Aborted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_LookAt_Aborted OnBTTask_LookAt_Aborted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual FRotator GetFinalLookAtRotation(AActor* Target, const FName &Bone);
	virtual FRotator GetFinalLookAtRotation(const FVector &Target);

	/** if LookTime == 0, then Look until aligned with Target.
		if LookTime < 0, then Look at Target forever / indefinitely
	*/
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void LookAtLocation(const FVector &Target, const float &LookRate, const float &LookTime);
	/** if LookTime == 0, then Look until aligned with Target.
		if LookTime < 0, then Look at Target forever / indefinitely
	*/
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void LookAtActor(AActor* Target, const FName &Bone, const float &LookRate, const float &LookTime);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void ResetLookAt(const float &BlendOutRate);
	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StopLookAt();

#pragma endregion LookAt

	// AimAt
#pragma region
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior Tree")
	float CurrentAimYaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior Tree")
	float CurrentAimPitch;

		// Location Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_AimAtLocation_Start, const uint8&, const FVector&);
	FOnBTTask_AimAtLocation_Start OnBTTask_AimAtLocation_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAtLocation_Start OnBTTask_AimAtLocation_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Actor Start
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBTTask_AimAtActor_Start, const uint8&, AActor*);
	FOnBTTask_AimAtActor_Start OnBTTask_AimAtActor_Start_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAtActor_Start OnBTTask_AimAtActor_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Abort
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_AimAt_Aborted, const uint8&);
	FOnBTTask_AimAt_Aborted OnBTTask_AimAt_Aborted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_AimAt_Aborted OnBTTask_AimAt_Aborted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void ResetAimAt(const float &BlendOutTime);

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
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Start OnBTTask_Shoot_Start_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Stop
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Shoot_Stop, const uint8&);
	FOnBTTask_Shoot_Stop OnBTTask_Shoot_Stop_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Stop OnBTTask_Shoot_Stop_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA
		// Abort
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBTTask_Shoot_Aborted, const uint8&);
	FOnBTTask_Shoot_Aborted OnBTTask_Shoot_Aborted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Behavior Tree")
	FBindableDynEvent_CsAIPawn_OnBTTask_Shoot_Aborted OnBTTask_Shoot_Aborted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UPROPERTY(BlueprintReadOnly, Category = "Behavior Tree")
	FECsGameEvent StartShootEvent;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StartShoot();

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	void StartShootForCount(const int32 &Count);
	static char StartShootForCount_Internal(FCsRoutine* r);
	FCsRoutine* StartShootForCount_Internal_Routine;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	void StartShootForDuration(const float &Duration);
	static char StartShootForDuration_Internal(FCsRoutine* r);
	FCsRoutine* StartShootForDuration_Internal_Routine;

	UPROPERTY(BlueprintReadOnly, Category = "Behavior Tree")
	FECsGameEvent StopShootEvent;

	UFUNCTION(BlueprintCallable, Category = "Behavior Tree")
	virtual void StopShoot();

	bool IsShooting();

#pragma endregion Shoot

#pragma endregion Behavior Tree

// Sense
#pragma region
public:

#pragma endregion Sense
};