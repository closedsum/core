// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "AI/Pawn/CsAIPawn.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Interactive.h"
#include "CsInteractiveAIPawn.generated.h"

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnInteraction, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnInteraction, const uint16&, const FCsInteractedActorInfo&);

// FirstFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstFreeze, const uint16&, const FCsInteractedActorInfo&);
// Freeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFreeze, const uint16&, const FCsInteractedActorInfo&);
// FirstUnFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstUnFreeze, const uint16&, const FCsInteractedActorInfo&);
// FirstHold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstHold, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstHold, const uint16&, const FCsInteractedActorInfo&);
// Hold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnHold, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnHold, const uint16&, const FCsInteractedActorInfo&);
// Release
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnRelease, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnRelease, const uint16&, const FCsInteractedActorInfo&);
// FirstTouch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstTouch, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstTouch, const uint16&, const FCsInteractedActorInfo&);
// Touch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnTouch, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnTouch, const uint16&, const FCsInteractedActorInfo&);
// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstHover, const uint16&, const FCsInteractedActorInfo&);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnHover, const uint16&, const FCsInteractedActorInfo&);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstUnHover, const uint16&, const FCsInteractedActorInfo&);
// FirstCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstCollide, const uint16&, const FCsInteractedActorInfo&);
// Collide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnCollide, const uint16&, const FCsInteractedActorInfo&);
// FirstUnCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnFirstUnCollide, const uint16&, const FCsInteractedActorInfo&);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveAIPawn_Override_OnRemove, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveAIPawn_OnRemove, const uint16&, const FCsInteractedActorInfo&);

// Enums
#pragma region

namespace ECsInteractiveAIPawnRoutine
{
	enum Type
	{
		ECsInteractiveAIPawnRoutine_MAX = ECsAIPawnRoutine::ECsAIPawnRoutine_MAX,
	};
}

namespace ECsInteractiveAIPawnRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return Type::ECsInteractiveAIPawnRoutine_MAX;
	}
}

#define ECS_INTERACTIVE_AI_PAWN_ROUTINE_MAX (uint8)ECsInteractiveAIPawnRoutine::ECsInteractiveAIPawnRoutine_MAX
typedef ECsInteractiveAIPawnRoutine::Type TCsInteractiveAIPawnRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsInteractiveAIPawn : public ACsAIPawn
{
	GENERATED_UCLASS_BODY()

	virtual void DeAllocate() override;

// State
#pragma region
public:

	TCsInteractiveState State;

	TMap<TCsInteractiveState, TArray<FCsInteractedActorInfo>> InteractedInfos;

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo& Info);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo& Info);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ClearInteractedInfos();

	TArray<FCsInteractedActorInfo>* GetInteractedInfos(const TEnumAsByte<ECsInteractiveState::Type> &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetInteractedInfos_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, TArray<FCsInteractedActorInfo> &OutInfos);

	FBindableEvent_CsInteractiveAIPawn_OnInteraction OnInteraction_Event;

	FBindableEvent_CsInteractiveAIPawn_OnFirstFreeze OnFirstFreeze_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFreeze OnFreeze_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstUnFreeze OnFirstUnFreeze_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstHold OnFirstHold_Event;
	FBindableEvent_CsInteractiveAIPawn_OnHold OnHold_Event;
	FBindableEvent_CsInteractiveAIPawn_OnRelease OnRelease_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstTouch OnFirstTouch_Event;
	FBindableEvent_CsInteractiveAIPawn_OnTouch OnTouch_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsInteractiveAIPawn_OnHover OnHover_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstCollide OnFirstCollide_Event;
	FBindableEvent_CsInteractiveAIPawn_OnCollide OnCollide_Event;
	FBindableEvent_CsInteractiveAIPawn_OnFirstUnCollide OnFirstUnCollide_Event;
	FBindableEvent_CsInteractiveAIPawn_OnRemove OnRemove_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstFreeze Override_OnFirstFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFreeze Override_OnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnFreeze Override_OnFirstUnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstHold Override_OnFirstHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnHold Override_OnHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnRelease Override_OnRelease_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstTouch Override_OnFirstTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnTouch Override_OnTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstCollide Override_OnFirstCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnCollide Override_OnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnFirstUnCollide Override_OnFirstUnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveAIPawn_Override_OnRemove Override_OnRemove_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info);

	virtual void OnInteraction(const FCsInteractedActorInfo &Info);

	virtual void OnFirstFreeze(const FCsInteractedActorInfo &Info);
	virtual void OnFreeze(const FCsInteractedActorInfo &Info);
	virtual void OnFirstUnFreeze(const FCsInteractedActorInfo &Info);
	virtual void OnFirstHold(const FCsInteractedActorInfo &Info);
	virtual void OnHold(const FCsInteractedActorInfo &Info);
	virtual void OnRelease(const FCsInteractedActorInfo &Info);
	virtual void OnFirstTouch(const FCsInteractedActorInfo &Info);
	virtual void OnTouch(const FCsInteractedActorInfo &Info);
	virtual void OnFirstHover(const FCsInteractedActorInfo &Info);
	virtual void OnHover(const FCsInteractedActorInfo &Info);
	virtual void OnFirstUnHover(const FCsInteractedActorInfo &Info);
	virtual void OnFirstCollide(const FCsInteractedActorInfo &Info);
	virtual void OnCollide(const FCsInteractedActorInfo &Info);
	virtual void OnFirstUnCollide(const FCsInteractedActorInfo &Info);
	virtual void OnRemove(const FCsInteractedActorInfo &Info);

	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeState(const TEnumAsByte<ECsInteractiveState::Type> &FromState, const TEnumAsByte<ECsInteractiveState::Type> &ToState);
	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeFromAnyState(const TArray<TEnumAsByte<ECsInteractiveState::Type>> &FromStates, const TEnumAsByte<ECsInteractiveState::Type> &ToState);

	virtual bool IsInTouchRange(UObject* InInstigator);
	virtual bool CanBeTouched(UObject* InInstigator);

#pragma endregion State

	virtual void Show();
	virtual void Hide();

	// Collision
#pragma region

	UPROPERTY(BlueprintReadOnly, Category = "Collision", meta = (Bitmask, BitmaskEnum = "ECsInteractivePhysicsState"))
	int32 PhysicsState;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	bool IsPhysicsState(const ECsInteractivePhysicsState &StateType);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SetPhysicsState(const ECsInteractivePhysicsState &StateType);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void ClearPhysicsState(const ECsInteractivePhysicsState &StateType);

	UPROPERTY(BlueprintReadWrite, Category = "Collision")
	TArray<float> PhysicsStateTimers;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void IncrementPhysicsStateTimer(const ECsInteractivePhysicsState &StateType, const float& Value);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SetPhysicsStateTimer(const ECsInteractivePhysicsState &StateType, const float& Value);

#pragma endregion Collision
};