// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsDamageableActor.generated.h"

// Despawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_OnDespawn, const int32&, Index);
// Respawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_OnRespawn, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_Override_Respawn, const int32&, Index);

// Enums
#pragma region

UENUM(BlueprintType)
enum class ECsDamageableActorRoutine : uint8
{
	Respawn_Internal				UMETA(DisplayName = "Respawn_Internal"),
	ECsDamageableActorRoutine_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDamageableActorRoutine : public TCsEnumMap<ECsDamageableActorRoutine>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsDamageableActorRoutine)
};

namespace NCsDamageableActorRoutine
{
	typedef ECsDamageableActorRoutine Type;

	namespace Ref
	{
		extern CSCORE_API const Type Respawn_Internal;
		extern CSCORE_API const Type ECsDamageableActorRoutine_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_DAMAGEABLE_ACTOR_ROUTINE_MAX NCsDamageableActorRoutine::MAX

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsDamageableActor : public ACsInteractiveActor
{
	GENERATED_UCLASS_BODY()

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& InType) override;
	virtual void ClearRoutines() override;

#pragma endregion Routines

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable", meta = (ClampMin = "0", UIMin = "0"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RespawnTime;

	virtual void Despawn();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDespawn, const int32&);

	FOnDespawn OnDespawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_OnDespawn OnDespawn_ScriptEvent;

	CS_COROUTINE_DECLARE(Respawn)

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRespawn, const int32&);

	FOnRespawn OnRespawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_OnRespawn OnRespawn_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_Override_Respawn Override_Respawn_ScriptEvent;

	virtual void ApplyDamage(FCsDamageEvent* Event);
};