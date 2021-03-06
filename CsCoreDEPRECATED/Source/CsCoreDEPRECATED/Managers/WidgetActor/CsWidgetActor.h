// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Interactive.h"
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

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsWidgetActorCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class ACsWidgetActor> WidgetActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class UUserWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsWidgetActorType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector2D DrawSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool bMinDrawDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FCsDrawDistance MinDrawDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool ScaleByDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	float DistanceProjectedOutFromCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool LookAtCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FCsRotatorFlag CameraLockAxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	bool bMovementFunction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FCsParametricFunction MovementFunction;

	FCsWidgetActorCache()
	{
		Reset();
	}

	void Set(const int32 &InIndex, ACsWidgetActor* InWidgetActor)
	{
		Index = InIndex;
		WidgetActor = InWidgetActor;
	}

	void Init(FCsWidgetActorPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		bAllocated = true;

		SetLifeTime(Payload->LifeTime);

		Owner	 = Payload->Owner;
		Widget = Payload->GetWidget();
		DrawSize = Payload->Size;
		bMinDrawDistance = Payload->bMinDrawDistance;
		MinDrawDistance = Payload->MinDrawDistance;
		ScaleByDistance = Payload->ScaleByDistance;
		Transform = Payload->Transform;
		Rotation = Transform.GetRotation().Rotator();
		Location = Transform.GetTranslation();
		Scale = Transform.GetScale3D();
		FollowCamera = Payload->FollowCamera;
		DistanceProjectedOutFromCamera = Payload->DistanceProjectedOutFromCamera;
		LookAtCamera = Payload->LookAtCamera;
		CameraLockAxes = Payload->LockAxes;
		bMovementFunction = Payload->bMovementFunction;
		MovementFunction = Payload->MovementFunction;
		MovementFunction.Seed();
		Parent	 = Payload->Parent;
		Time	 = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Widget.Reset();
		Widget = nullptr;
		DrawSize = FVector2D::ZeroVector;
		bMinDrawDistance = false;
		MinDrawDistance.Reset();
		ScaleByDistance = false;
		Transform = FTransform::Identity;
		Rotation = FRotator::ZeroRotator;
		Location = FVector::ZeroVector;
		Scale = FVector::OneVector;
		FollowCamera = false;
		DistanceProjectedOutFromCamera = 0.0f;;
		LookAtCamera = false;
		bMovementFunction = false;
	}

	ACsWidgetActor* GetWidgetActor() { return WidgetActor.IsValid() ? WidgetActor.Get() : nullptr; }
	template<typename T>
	T* GetWidgetActor(){ return Cast<T>(GetWidgetActor()) }

	class UUserWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
	template<typename T>
	T* GetWidget() { return Cast<T>(GetWidget()); }
};

UCLASS()
class CSCOREDEPRECATED_API ACsWidgetActor : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	class UCsWidgetComponent* WidgetComponent;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	FECsWidgetActorType Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	FCsWidgetActorCache Cache;

	void Init(const int32 &Index, const FECsWidgetActorType &InType);

// Allocate / DeAllocate
#pragma region
public:

	void Allocate(FCsWidgetActorPayload* Payload);

	virtual void Allocate_Internal(FCsWidgetActorPayload* Payload);

	virtual void DeAllocate() override;

#pragma endregion Allocate / DeAllocate

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtLocalCamera;

// Widget
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UUserWidget* MyWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool bCacheWidget;

#pragma endregion Widget

// Camera
#pragma region
public:

	void OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult);

	UPROPERTY(BlueprintAssignable, Category = "Camera")
	FBindableDynEvent_CsWidgetActor_Override_OnCalcCamera Override_OnCalcCamera_ScriptEvent;

	void OnTick_Handle_LocalCamera(const FVector &ViewLocation, const FRotator &ViewRotation);

#pragma endregion Camera

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

	void OnTick_Handle_Scale();

#pragma endregion State

// Visibility
#pragma region
public:

	virtual void Show() override;
	virtual void Hide() override;

	void OnTick_Handle_DrawDistance();

#pragma endregion Visiblity

// Movement
#pragma region
public:

	void OnTick_HandleMovementFunction();

#pragma endregion Movement
};