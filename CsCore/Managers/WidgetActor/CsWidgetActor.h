// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Managers/CsPooledActor.h"
#include "UI/CsUserWidget.h"
#include "CsWidgetActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBindableDynEvent_CsWidgetActor_Override_OnCalcCamera, const int32&, Index, const uint8&, MappingId, const float&, DeltaTime, const struct FMinimalViewInfo&, ViewInfo);

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnInteraction, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnInteraction, const uint16&, const FCsInteractedActorInfo&);

// FirstFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstFreeze, const uint16&, const FCsInteractedActorInfo&);
// Freeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFreeze, const uint16&, const FCsInteractedActorInfo&);
// FirstUnFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstUnFreeze, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstUnFreeze, const uint16&, const FCsInteractedActorInfo&);
// FirstHold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstHold, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstHold, const uint16&, const FCsInteractedActorInfo&);
// Hold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnHold, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnHold, const uint16&, const FCsInteractedActorInfo&);
// Release
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnRelease, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnRelease, const uint16&, const FCsInteractedActorInfo&);
// FirstTouch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstTouch, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstTouch, const uint16&, const FCsInteractedActorInfo&);
// Touch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnTouch, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnTouch, const uint16&, const FCsInteractedActorInfo&);
// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstHover, const uint16&, const FCsInteractedActorInfo&);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnHover, const uint16&, const FCsInteractedActorInfo&);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstUnHover, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstUnHover, const uint16&, const FCsInteractedActorInfo&);
// FirstCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstCollide, const uint16&, const FCsInteractedActorInfo&);
// Collide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnCollide, const uint16&, const FCsInteractedActorInfo&);
// FirstUnCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnFirstUnCollide, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnFirstUnCollide, const uint16&, const FCsInteractedActorInfo&);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWidgetActor_Override_OnRemove, const int32&, Index, const FCsInteractedActorInfo&, Info);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWidgetActor_OnRemove, const uint16&, const FCsInteractedActorInfo&);

USTRUCT()
struct FCsWidgetActorCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsWidgetActor> WidgetActor;
	TWeakObjectPtr<class UCsUserWidget> Widget;

	// TODO: LifeTime. Need a struct for holding WidgetActor information (FCsWidgetActor?)

	FCsWidgetActorCache()
	{
		Reset();
	}

	void Set(const uint16 &InIndex, ACsWidgetActor* InWidgetActor)
	{
		Index	    = InIndex;
		WidgetActor = InWidgetActor;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, class UCsUserWidget* InWidget, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Widget = InWidget;
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
	void Init(const uint16& InActiveIndex, class UCsUserWidget* InWidget, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InWidget, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, class UCsUserWidget* InWidget, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Widget = InWidget;
		Parent = InParent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	void Init(const uint16& InActiveIndex, class UCsUserWidget* InWidget, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InWidget, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		Super::Reset();

		WidgetActor.Reset();
		WidgetActor = nullptr;
		Widget.Reset();
		Widget = nullptr;
	}

	ACsWidgetActor* GetWidgetActor() { return WidgetActor.IsValid() ? WidgetActor.Get() : nullptr; }
	class UCsUserWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsWidgetActor : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	class UWidgetComponent* WidgetComponent;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	void OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult);

	UPROPERTY(BlueprintAssignable, Category = "Camera")
	FBindableDynEvent_CsWidgetActor_Override_OnCalcCamera Override_OnCalcCamera_ScriptEvent;

	TCsWidgetActorType Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	uint8 Type_Script;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	FCsWidgetActorCache Cache;

	void Init(const int32 &Index, const TCsWidgetActorType &InType);

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, class UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, class UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	void Allocate(const uint16 &ActiveIndex, class UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	void Allocate(const uint16 &ActiveIndex, class UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame);

	virtual void Allocate_Internal(class UCsUserWidget* InWidget);

	virtual void DeAllocate() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtLocalCamera;

	// State
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TEnumAsByte<ECsInteractiveState::Type> State;

	FBindableEvent_CsWidgetActor_OnInteraction OnInteraction_Event;

	FBindableEvent_CsWidgetActor_OnFirstFreeze OnFirstFreeze_Event;
	FBindableEvent_CsWidgetActor_OnFreeze OnFreeze_Event;
	FBindableEvent_CsWidgetActor_OnFirstUnFreeze OnFirstUnFreeze_Event;
	FBindableEvent_CsWidgetActor_OnFirstHold OnFirstHold_Event;
	FBindableEvent_CsWidgetActor_OnHold OnHold_Event;
	FBindableEvent_CsWidgetActor_OnRelease OnRelease_Event;
	FBindableEvent_CsWidgetActor_OnFirstTouch OnFirstTouch_Event;
	FBindableEvent_CsWidgetActor_OnTouch OnTouch_Event;
	FBindableEvent_CsWidgetActor_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsWidgetActor_OnHover OnHover_Event;
	FBindableEvent_CsWidgetActor_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsWidgetActor_OnFirstCollide OnFirstCollide_Event;
	FBindableEvent_CsWidgetActor_OnCollide OnCollide_Event;
	FBindableEvent_CsWidgetActor_OnFirstUnCollide OnFirstUnCollide_Event;
	FBindableEvent_CsWidgetActor_OnRemove OnRemove_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstFreeze Override_OnFirstFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFreeze Override_OnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstUnFreeze Override_OnFirstUnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstHold Override_OnFirstHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnHold Override_OnHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnRelease Override_OnRelease_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstTouch Override_OnFirstTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnTouch Override_OnTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstCollide Override_OnFirstCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnCollide Override_OnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnFirstUnCollide Override_OnFirstUnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWidgetActor_Override_OnRemove Override_OnRemove_ScriptEvent;

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

#pragma endregion State

	virtual void Show() override;
	virtual void Hide() override;
};