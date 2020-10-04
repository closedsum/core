// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Event/CsStatusEffectEventInfo.h"
#include "CsReceiveStatusEffect.h"
#include "Managers/Time/CsTypes_Time.h"
#include "CsManager_StatusEffect.generated.h"

// Structs
#pragma region

	// StatusEffectEventInfo

struct CSSE_API FCsResource_StatusEffectEventInfo : public TCsResourceContainer<NCsStatusEffect::NEvent::FInfo>
{
};

struct CSSE_API FCsManager_StatusEffectEventInfo : public TCsManager_ResourceValueType_Fixed<NCsStatusEffect::NEvent::FInfo, FCsResource_StatusEffectEventInfo, 0>
{
};

#pragma endregion Structs

namespace NCsStatusEffect {
	namespace NEvent {
		struct IEvent; } }

struct FCsResource_StatusEffectEvent;

UCLASS()
class CSSE_API UCsManager_StatusEffect : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventType NCsStatusEffect::NEvent::IEvent

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

	void Update(const FCsDeltaTime& DeltaTime);

private:

	FCsManager_StatusEffectEventInfo Manager_Event;

public:

	void ApplyStatusEffect(FCsResource_StatusEffectEvent* Event);

	void ApplyStatusEffect(EventType* Event);

#undef EventType
};