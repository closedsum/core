// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsDamageableActor.generated.h"

// Despawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_OnDespawn, const int32&, Index);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsDamageableActor_OnDespawn, const uint16&);
// Respawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_OnRespawn, const int32&, Index);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsDamageableActor_OnRespawn, const uint16&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsDamageableActor_Override_Respawn, const int32&, Index);

UCLASS()
class CSCORE_API ACsDamageableActor : public ACsInteractiveActor
{
	GENERATED_UCLASS_BODY()

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual void ClearRoutines() override;

#pragma endregion Routines

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable", meta = (ClampMin = "0", UIMin = "0"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RespawnTime;

	virtual void Despawn();

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_OnDespawn OnDespawn_ScriptEvent;

	FBindableEvent_CsDamageableActor_OnDespawn OnDespawn_Event;

	CS_COROUTINE_DECLARE(Respawn)

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_OnRespawn OnRespawn_ScriptEvent;

	FBindableEvent_CsDamageableActor_OnRespawn OnRespawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "Damageable")
	FBindableDynEvent_CsDamageableActor_Override_Respawn Override_Respawn_ScriptEvent;

	virtual void ApplyDamage(FCsDamageEvent* Event);
};