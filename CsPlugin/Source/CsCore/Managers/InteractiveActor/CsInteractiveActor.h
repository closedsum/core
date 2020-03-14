// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsPooledActor.h"
// Types
#include "Types/Property/Value/CsProperty_Vector2D.h"
#include "Types/Property/Value/CsProperty_Vector.h"
#include "Types/CsTypes_Interactive.h"
#include "Data/CsData_Interactive.h"
#include "CsInteractiveActor.generated.h"

// Macros
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsInteractiveActor_Override_OnTickOverlap, const int32&, Index, const float&, DeltaSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FBindableDynEvent_CsInteractiveActor_Override_OnBeginOverlap, const int32&, Index, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FBindableDynEvent_CsInteractiveActor_Override_OnEndOverlap, const int32&, Index, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnInteraction, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsInteractiveActor_OnInteraction, const uint16&, UObject*);

// FirstFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstFreeze, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstFreeze, const uint16&, UObject*, USceneComponent*);
// Freeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFreeze, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFreeze, const uint16&, UObject*, USceneComponent*);
// FirstUnFreeze
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnFreeze, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstUnFreeze, const uint16&, UObject*, USceneComponent*);
// FirstHold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstHold, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstHold, const uint16&, UObject*, USceneComponent*);
// Hold
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnHold, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnHold, const uint16&, UObject*, USceneComponent*);
// Release
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnRelease, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnRelease, const uint16&, UObject*, USceneComponent*);
// FirstTouch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstTouch, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstTouch, const uint16&, UObject*, USceneComponent*);
// Touch
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnTouch, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnTouch, const uint16&, UObject*, USceneComponent*);
// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstHover, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstHover, const uint16&, UObject*, USceneComponent*);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnHover, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnHover, const uint16&, UObject*, USceneComponent*);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnHover, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstUnHover, const uint16&, UObject*, USceneComponent*);
// FirstCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstCollide, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstCollide, const uint16&, UObject*, USceneComponent*);
// Collide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnCollide, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnCollide, const uint16&, UObject*, USceneComponent*);
// FirstUnCollide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnCollide, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnFirstUnCollide, const uint16&, UObject*, USceneComponent*);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsInteractiveActor_Override_OnRemove, const int32&, Index, UObject*, InInstigator, USceneComponent*, InComponent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsInteractiveActor_OnRemove, const uint16&, UObject*, USceneComponent*);

#pragma endregion Macros

// Enums
#pragma region

namespace ECsInteractiveActorRoutine
{
	enum Type
	{
		ECsInteractiveActorRoutine_MAX = ECsPooledActorRoutine::ECsPooledActorRoutine_MAX,
	};
}

#define ECS_INTERACTIVE_ACTOR_ROUTINE_MAX (uint8)ECsInteractiveActorRoutine::ECsInteractiveActorRoutine_MAX
typedef ECsInteractiveActorRoutine::Type TCsInteractiveActorRoutine;

namespace ECsInteractiveActorRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	namespace Ref
	{
		const TCsInteractiveActorRoutine ECsInteractiveActorRoutine_MAX = Type::ECsInteractiveActorRoutine_MAX;
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		return Ref::ECsInteractiveActorRoutine_MAX;
	}
}

#pragma endregion Enums

class ACsInteractiveActor;
class UCsData_Interactive;

USTRUCT(BlueprintType)
struct FCsInteractiveActorCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<ACsInteractiveActor> Actor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<UCsData_Interactive> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FECsInteractiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Scale;

	FCsInteractiveActorCache()
	{
		Reset();
	}

	~FCsInteractiveActorCache(){}

	void Set(const int32 &InIndex, class ACsInteractiveActor* InActor)
	{
		Index = InIndex;
		Actor = InActor;
	}

	void Init(FCsInteractiveActorPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Data = Payload->GetData();
		Owner = Payload->Owner;
		Parent = Payload->Parent;

		WarmUpTime = Data->GetWarmUpTime();
		State = WarmUpTime > 0.0f ? ECsPooledObjectState::WarmUp : ECsPooledObjectState::Active;

		Transform = Payload->Transform;
		Rotation = Transform.GetRotation().Rotator();
		Location = Transform.GetTranslation();
		Scale = Transform.GetScale3D();

		SetLifeTime(Data->GetLifeTime());

		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Actor.Reset();
		Actor = nullptr;
		Data.Reset();
		Data = nullptr;

		Transform = FTransform::Identity;
		Rotation = FRotator::ZeroRotator;
		Location = FVector::ZeroVector;
		Scale = FVector::OneVector;
	}

	FORCEINLINE ACsInteractiveActor* GetActor() { return Actor.IsValid() ? Actor.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetActor() { return Cast<T>(GetActor()); }

	FORCEINLINE UCsData_Interactive* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }
};

UCLASS()
class CSCORE_API ACsInteractiveActor : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	bool UseSkeletalMesh;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UCsSkeletalMeshComponent* SkeletalMeshComponent;
protected:
	bool UseStaticMesh;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UCsStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Collision")
	class UPrimitiveComponent* WorldCollisionComponent;

	bool WorldCollisionSimulatesPhysics;

protected:
	bool UseBoxCollision;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	class UCsBoxComponent* BoxComponent;
protected:
	bool UseSphereCollision;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	class UCsSphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UPrimitiveComponent* InteractiveCollisionComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECollisionEnabled::Type> InteractiveCollisionEnabled;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	FECsInteractiveType Type;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	TEnumAsByte<ECsInteractiveCollision::Type> CollisionType;

	TArray<TWeakObjectPtr<AActor>> CollidableActors;
	TArray<TWeakObjectPtr<AActor>> IgnoredActors;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	FCsInteractiveActorCache Cache;

	void Init(const int32 &Index, const FECsInteractiveType &InType);

// Allocate / DeAllocate
#pragma region
public:

	template<typename T>
	void Allocate(FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(FCsInteractiveActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	void Allocate(FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* InParent);
	void Allocate(FCsInteractiveActorPayload* Payload);

	virtual void Allocate_Internal(FCsInteractiveActorPayload* Payload);

	virtual void DeAllocate() override;

#pragma endregion Allocate / DeAllocate

// State
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TEnumAsByte<ECsInteractiveState::Type> State;

	// InteractedInfo
#pragma region
	TMap<TCsInteractiveState, TArray<FCsInteractedActorInfo>> InteractedInfos;

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ClearInteractedInfos();

	TArray<FCsInteractedActorInfo>* GetInteractedInfos(const TEnumAsByte<ECsInteractiveState::Type> &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetInteractedInfos_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, TArray<FCsInteractedActorInfo> &OutInfos);
#pragma endregion InteractedInfo

	FBindableEvent_CsInteractiveActor_OnInteraction OnInteraction_Event;

	FBindableEvent_CsInteractiveActor_OnFirstFreeze OnFirstFreeze_Event;
	FBindableEvent_CsInteractiveActor_OnFreeze OnFreeze_Event;
	FBindableEvent_CsInteractiveActor_OnFirstUnFreeze OnFirstUnFreeze_Event;
	FBindableEvent_CsInteractiveActor_OnFirstHold OnFirstHold_Event;
	FBindableEvent_CsInteractiveActor_OnHold OnHold_Event;
	FBindableEvent_CsInteractiveActor_OnRelease OnRelease_Event;
	FBindableEvent_CsInteractiveActor_OnFirstTouch OnFirstTouch_Event;
	FBindableEvent_CsInteractiveActor_OnTouch OnTouch_Event;
	FBindableEvent_CsInteractiveActor_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsInteractiveActor_OnHover OnHover_Event;
	FBindableEvent_CsInteractiveActor_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsInteractiveActor_OnFirstCollide OnFirstCollide_Event;
	FBindableEvent_CsInteractiveActor_OnCollide OnCollide_Event;
	FBindableEvent_CsInteractiveActor_OnFirstUnCollide OnFirstUnCollide_Event;
	FBindableEvent_CsInteractiveActor_OnRemove OnRemove_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstFreeze Override_OnFirstFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFreeze Override_OnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnFreeze Override_OnFirstUnFreeze_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstHold Override_OnFirstHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnHold Override_OnHold_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnRelease Override_OnRelease_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstTouch Override_OnFirstTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnTouch Override_OnTouch_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstCollide Override_OnFirstCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnCollide Override_OnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnFirstUnCollide Override_OnFirstUnCollide_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsInteractiveActor_Override_OnRemove Override_OnRemove_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo& Info);

	virtual void OnInteraction(const FCsInteractedActorInfo& Info);

	virtual void OnFirstFreeze(const FCsInteractedActorInfo& Info);
	virtual void OnFreeze(const FCsInteractedActorInfo& Info);
	virtual void OnFirstUnFreeze(const FCsInteractedActorInfo& Info);
	virtual void OnFirstHold(const FCsInteractedActorInfo& Info);
	virtual void OnHold(const FCsInteractedActorInfo& Info);
	virtual void OnRelease(const FCsInteractedActorInfo& Info);
	virtual void OnFirstTouch(const FCsInteractedActorInfo& Info);
	virtual void OnTouch(const FCsInteractedActorInfo& Info);
	virtual void OnFirstHover(const FCsInteractedActorInfo& Info);
	virtual void OnHover(const FCsInteractedActorInfo& Info);
	virtual void OnFirstUnHover(const FCsInteractedActorInfo& Info);
	virtual void OnFirstCollide(const FCsInteractedActorInfo& Info);
	virtual void OnCollide(const FCsInteractedActorInfo& Info);
	virtual void OnFirstUnCollide(const FCsInteractedActorInfo& Info);
	virtual void OnRemove(const FCsInteractedActorInfo& Info);

	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeState(const TEnumAsByte<ECsInteractiveState::Type> &FromState, const TEnumAsByte<ECsInteractiveState::Type> &ToState);
	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeFromAnyState(const TArray<TEnumAsByte<ECsInteractiveState::Type>> &FromStates, const TEnumAsByte<ECsInteractiveState::Type> &ToState);

	UFUNCTION(BlueprintCallable, Category = "State")
	class ACsMotionController* GetDominantHand_HoldingMe();
	UFUNCTION(BlueprintCallable, Category = "State")
	class ACsMotionController* GetLastHand_HoveringOverMe();

#pragma endregion State

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;

#pragma endregion Routines

// Visibility
#pragma region
public:

	virtual void Show() override;
	virtual void Hide() override;

#pragma endregion Visibility

// Collision
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	float MinPhysicsLinearVelocityForMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	float MinPhysicsAngularVelocityForMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Collision", meta = (Bitmask, BitmaskEnum = "ECsInteractivePhysicsState"))
	int32 PhysicsState;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	bool IsPhysicsState(const ECsInteractivePhysicsState &StateType);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SetPhysicsState(const ECsInteractivePhysicsState &StateType);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void ClearPhysicsState(const ECsInteractivePhysicsState &StateType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	bool CheckIsAirborne;

	virtual void OnTick_Handle_PhysicsState();
	virtual void OnTick_Overlap(const float DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FBindableDynEvent_CsInteractiveActor_Override_OnTickOverlap Override_OnTickOverlap_ScriptEvent;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FBindableDynEvent_CsInteractiveActor_Override_OnBeginOverlap Override_OnBeginOverlap_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FBindableDynEvent_CsInteractiveActor_Override_OnEndOverlap Override_OnEndOverlap_ScriptEvent;

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Collision")
	bool CanCollideWithComponent(UPrimitiveComponent* InComponent);

#pragma endregion Collision

// UI
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	bool bCalculateScreenPosition;

	virtual void CalculateScreenPosition();

	TCsFVector2D ScreenPosition;
	TCsFVector WorldPosition;

#pragma endregion UI
};