// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Interactive.h"
#include "UI/CsTypes_UI.h"
#include "CsMotionController.generated.h"

// Delegates
#pragma region

// Interactives
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBindableDynEvent_CsMotionController_Override_OnCalcCamera, const uint8&, MappingId, const ECsControllerHand&, InHand, const float&, DeltaTime, const struct FMinimalViewInfo&, ViewInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FBindableDynEvent_CsMotionController_Override_OnBeginOverlap, const ECsControllerHand&, Hand, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnInteraction, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnInteraction, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);

// FirstFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstFreeze, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstFreeze, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Freeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFreeze, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFreeze, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstUnFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstUnFreeze, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstUnFreeze, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstHold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstHold, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstHold, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Hold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnHold, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnHold, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Release
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnRelease, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnRelease, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstTouch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstTouch, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstTouch, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Touch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnTouch, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnTouch, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstHover, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstHover, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnHover, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnHover, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstUnHover, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstUnHover, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstCollide, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstCollide, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Collide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnCollide, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnCollide, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// FirstUnCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnFirstUnCollide, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnFirstUnCollide, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnRemove, const ECsControllerHand&, Hand, const TArray<FCsInteractedActorInfo>&, Infos);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnRemove, const ECsControllerHand&, const TArray<FCsInteractedActorInfo>&);

#pragma endregion Interactives

// Buttons
#pragma region

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonInteraction, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonInteraction, const ECsControllerHand&, const TArray<USceneComponent*>&);

// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonFirstHover, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonFirstHover, const ECsControllerHand&, const TArray<USceneComponent*>&);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonHover, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonHover, const ECsControllerHand&, const TArray<USceneComponent*>&);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonFirstUnHover, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonFirstUnHover, const ECsControllerHand&, const TArray<USceneComponent*>&);
// FirstPressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonFirstPressed, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonFirstPressed, const ECsControllerHand&, const TArray<USceneComponent*>&);
// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonPressed, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonPressed, const ECsControllerHand&, const TArray<USceneComponent*>&);
// FirstReleased
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsMotionController_Override_OnButtonFirstReleased, const ECsControllerHand&, Hand, const TArray<USceneComponent*>&, Buttons);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsMotionController_OnButtonFirstReleased, const ECsControllerHand&, const TArray<USceneComponent*>&);

#pragma endregion Buttons

#pragma endregion Delegates

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsRoutineMotionController
{
	enum Type
	{
		Setup_OnCalcCamera_Internal		UMETA(DisplayName = "Setup_OnCalcCamera_Internal"),
		ECsRoutineMotionController_MAX	UMETA(Hidden),
	};
}

namespace ECsRoutineMotionController
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Setup_OnCalcCamera_Internal = TCsString(TEXT("Setup_OnCalcCamera_Internal"), TEXT("setup_oncalccamera_internal"), TEXT("setup on calc camera internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Setup_OnCalcCamera_Internal) { return Str::Setup_OnCalcCamera_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Setup_OnCalcCamera_Internal) { return Type::Setup_OnCalcCamera_Internal; }
		return Type::ECsRoutineMotionController_MAX;
	}
}

#define ECS_ROUTINE_MOTION_CONTROLLER_MAX (uint8)ECsRoutineMotionController::ECsRoutineMotionController_MAX
typedef ECsRoutineMotionController::Type TCsRoutineMotionController;

#pragma endregion Enums

#define CS_MOTION_CONTROLLER_INFINITE_TRACE_COUNT -1

UCLASS()
class CSCORE_API ACsMotionController : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void PostActorCreated() override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	virtual void OutsideWorldBounds() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion")
	class USceneComponent* DefaultRootComponent;

	TWeakObjectPtr<class UMotionControllerComponent> MotionControllerComponent;

	class UMotionControllerComponent* GetMotionControllerComponent();

	FVector GetLocation();

	bool UseSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	bool UseStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	class UPrimitiveComponent* InteractiveCollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion")
	class USceneComponent* AnchorComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion")
	ECsControllerHand Hand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion")
	TWeakObjectPtr<class ACsMotionController> OtherHand;

	UFUNCTION(BlueprintCallable, Category = "Motion")
	class ACsMotionController* GetOtherHand();

	virtual void OnTick(const float &DeltaSeconds);
	virtual void OnTick_HandleCVars(const float &DeltaSeconds);
	virtual void OnTick_Check_FirstTouch(const float &DeltaSeconds);
	virtual void OnTick_Handle_FirstHoldAndHold(const float &DeltaSeconds);

	virtual void Init(class UMotionControllerComponent* InComponent, const ECsControllerHand &InHand);

// Touch
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Touch", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxTouchSenseRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Touch")
	FVector TouchSenseOffset;

	UFUNCTION(BlueprintCallable, Category = "Touch")
	FVector GetTouchSenseLocation();

#pragma endregion Touch

// Collision
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECsInteractiveCollision::Type> CollisionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	FCsCollisionPreset CollisionPreset;

	virtual void SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset);
	virtual void SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset, const FVector &BoxExtent);
	virtual void SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset, const float &SphereRadius);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FBindableDynEvent_CsMotionController_Override_OnBeginOverlap Override_OnBeginOverlap_ScriptEvent;

#pragma endregion Collision

	virtual void UpdateLocation(const FVector &Location);
	virtual void UpdateRotation(const FRotator &Rotaiton);
	virtual void UpdateLocationAndRotation(const FVector &Location, const FRotator &Rotation);

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InMotionController, struct FCsRoutine* Routine, const uint8 &Type);
	void AddRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineMotionController &Type);

	static void RemoveRoutine(UObject* InMotionController, struct FCsRoutine* Routine, const uint8 &Type);
	void RemoveRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineMotionController &Type);

#pragma endregion Routines

// Camera
#pragma region
public:

	void Setup_OnCalcCamera();
	static char Setup_OnCalcCamera_Internal(FCsRoutine* r);
	struct FCsRoutine* Setup_OnCalcCamera_Internal_Routine;

	UPROPERTY(BlueprintAssignable, Category = "Camera")
	FBindableDynEvent_CsMotionController_Override_OnCalcCamera Override_OnCalcCamera_ScriptEvent;

	virtual void OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &ViewInfo);

	int32 MaxTraceCount;
	float MaxTraceRange;
	float LastTrace_StartTime;
	FVector LastTraceHitLocation;
	AActor* LastTraceHitActor;

	virtual void OnCalcCamera_Trace(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &ViewInfo);
	virtual void OnCalcCamera_Trace_UpdateComponents();

#pragma endregion Camera

// State
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	TEnumAsByte<ECsInteractiveState::Type> State;

	TArray<TWeakObjectPtr<AActor>> CurrentInteractiveActors;
	TArray<FCsInteractedActorInfo> CurrentInteractedActorInfos;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	TArray<TEnumAsByte<ECsInteractiveState::Type>> CurrentInteractiveActorStates;

	// Blueprint
#pragma region
	UFUNCTION(BlueprintCallable, Category = "State")
	int32 GetCurrentInteractedActorInfosSize();
	UFUNCTION(BlueprintCallable, Category = "State")
	AActor* GetCurrentInteractedActor(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "State")
	void AddCurrentInteractedActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveCurrentInteractedActorInfo(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ResetCurrentInteractedActorInfos();
#pragma endregion Blueprint

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetCurrentInteractiveActors(const TEnumAsByte<ECsInteractiveState::Type> &StateType, TArray<AActor*> &OutActors);

	FBindableEvent_CsMotionController_OnInteraction OnInteraction_Event;

	FBindableEvent_CsMotionController_OnFirstFreeze OnFirstFreeze_Event;
	FBindableEvent_CsMotionController_OnFreeze OnFreeze_Event;
	FBindableEvent_CsMotionController_OnFirstUnFreeze OnFirstUnFreeze_Event;
	FBindableEvent_CsMotionController_OnFirstHold OnFirstHold_Event;
	FBindableEvent_CsMotionController_OnHold OnHold_Event;
	FBindableEvent_CsMotionController_OnRelease OnRelease_Event;
	FBindableEvent_CsMotionController_OnFirstTouch OnFirstTouch_Event;
	FBindableEvent_CsMotionController_OnTouch OnTouch_Event;
	FBindableEvent_CsMotionController_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsMotionController_OnHover OnHover_Event;
	FBindableEvent_CsMotionController_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsMotionController_OnFirstCollide OnFirstCollide_Event;
	FBindableEvent_CsMotionController_OnCollide OnCollide_Event;
	FBindableEvent_CsMotionController_OnFirstUnCollide OnFirstUnCollide_Event;
	FBindableEvent_CsMotionController_OnRemove OnRemove_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstFreeze Override_OnFirstFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFreeze Override_OnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstUnFreeze Override_OnFirstUnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstHold Override_OnFirstHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnHold Override_OnHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnRelease Override_OnRelease_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstTouch Override_OnFirstTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnTouch Override_OnTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstCollide Override_OnFirstCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnCollide Override_OnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnFirstUnCollide Override_OnFirstUnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnRemove Override_OnRemove_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const TArray<FCsInteractedActorInfo> &Infos);

	virtual void OnInteraction(const TArray<FCsInteractedActorInfo> &Infos);

	virtual void OnFirstFreeze(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFreeze(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstUnFreeze(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstHold(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnHold(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnRelease(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstTouch(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnTouch(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstHover(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnHover(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstUnHover(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstCollide(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnCollide(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnFirstUnCollide(const TArray<FCsInteractedActorInfo> &Infos);
	virtual void OnRemove(const TArray<FCsInteractedActorInfo> &Infos);

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsInteractingWith(const TEnumAsByte<ECsInteractiveState::Type> &InState, AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsInteractingWithAny(const TEnumAsByte<ECsInteractiveState::Type> &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHolding(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHoldingAny();
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHoveringOver(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHoveringOverAny();

#pragma endregion State

// Button State
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Button State")
	ECsButtonState ButtonState;

	TArray<TWeakObjectPtr<USceneComponent>> CurrentButtons;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Button State")
	TArray<ECsButtonState> CurrentButtonStates;

	UFUNCTION(BlueprintCallable, Category = "Button State")
	void GetCurrentButtons(const ECsButtonState &StateType, TArray<USceneComponent*> &OutButtons);

	FBindableEvent_CsMotionController_OnButtonInteraction OnButtonInteraction_Event;

	FBindableEvent_CsMotionController_OnButtonFirstHover OnButtonFirstHover_Event;
	FBindableEvent_CsMotionController_OnButtonHover OnButtonHover_Event;
	FBindableEvent_CsMotionController_OnButtonFirstUnHover OnButtonFirstUnHover_Event;
	FBindableEvent_CsMotionController_OnButtonFirstPressed OnButtonFirstPressed_Event;
	FBindableEvent_CsMotionController_OnButtonPressed OnButtonPressed_Event;
	FBindableEvent_CsMotionController_OnButtonFirstReleased OnButtonFirstReleased_Event;

#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonInteraction Override_OnButtonInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonFirstHover Override_OnButtonFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonHover Override_OnButtonHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonFirstUnHover Override_OnButtonFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonFirstPressed Override_OnButtonFirstPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonPressed Override_OnButtonPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsMotionController_Override_OnButtonFirstReleased Override_OnFirstReleased_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnButtonInteraction_Script(const ECsButtonState &InState, const TArray<USceneComponent*> Buttons);

	virtual void OnButtonInteraction(const TArray<USceneComponent*> &Buttons);

	virtual void OnButtonFirstHover(const TArray<USceneComponent*> &Buttons);
	virtual void OnButtonHover(const TArray<USceneComponent*> &Buttons);
	virtual void OnButtonFirstUnHover(const TArray<USceneComponent*> &Buttons);
	virtual void OnButtonFirstPressed(const TArray<USceneComponent*> &Buttons);
	virtual void OnButtonPressed(const TArray<USceneComponent*> &Buttons);
	virtual void OnButtonFirstReleased(const TArray<USceneComponent*> &Buttons);

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsInteractingWithButton(const ECsButtonState &InState, USceneComponent* InButton);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsInteractingWithAnyButton(const ECsButtonState &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHoveringOverButton(USceneComponent* InButton);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsHoveringOverAnyButton();

#pragma endregion Button State

	virtual void Show();
	virtual void Hide();
};