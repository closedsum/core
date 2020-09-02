// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
// Types
#include "Types/CsTypes.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsPooledActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPooledActor_Override_OnTick, const int32&, Index, const float&, DeltaSeconds);

// Enums
#pragma region

namespace ECsPooledActorRoutine
{
	enum Type
	{
		ECsPooledActorRoutine_MAX,
	};
}

#define ECS_POOLED_ACTOR_ROUTINE_MAX (uint8)ECsPooledActorRoutine::ECsPooledActorRoutine_MAX
typedef ECsPooledActorRoutine::Type TCsPooledActorRoutine;

namespace ECsPooledActorRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	namespace Ref
	{
		const TCsPooledActorRoutine ECsPooledActorRoutine_MAX = Type::ECsPooledActorRoutine_MAX;
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		return Ref::ECsPooledActorRoutine_MAX;
	}
}

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsPooledActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	virtual void OutsideWorldBounds() override;

	FString Warning_FellOutOfWorld;
	FString Warning_OutsideWorldBounds;

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsPooledActor_Override_OnTick Override_OnTick_ScriptEvent;

	virtual void OnTick(const float &DeltaSeconds);
	virtual void OnTick_HandleCVars(const float &DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	virtual void DeAllocate();

	virtual void OnCreatePool();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	bool IsPlaceable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	TEnumAsByte<ECsVisibility::Type> Visibility;

// Visibility
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Hide();

#pragma endregion Visiblity

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InObject, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	static void RemoveRoutine(UObject* InObject, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	virtual void ClearRoutines();

#pragma endregion Routines
};