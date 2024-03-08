// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
// StatusEffect
#include "Event/CsStatusEffectEventInfo.h"
#include "CsReceiveStatusEffect.h"
#include "CsResource_Allocated_StatusEffect.h"

#include "CsManager_StatusEffect.generated.h"


// NCsStatusEffect::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, IEvent)

UCLASS()
class CSSE_API UCsManager_StatusEffect : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventType NCsStatusEffect::NEvent::IEvent

#define AllocatedManagerType NCsStatusEffect::NAllocated::FManager

public:

	void Init(UObject* InRoot);

	void Shutdown(UObject* InRoot = nullptr);

	// Root
#pragma region
protected:

	FCsReceiveStatusEffect MyRoot;

	void SetMyRoot(UObject* InRoot);

public:
	 
	FORCEINLINE const FCsReceiveStatusEffect& GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

public:

	void CreatePool(const int32& PoolSize);

	void Update(const FCsDeltaTime& DeltaTime);

private:

	AllocatedManagerType Manager_Allocated;


public:

	void ApplyStatusEffect(EventType* Event);

#undef EventType

#undef AllocatedManagerType
};