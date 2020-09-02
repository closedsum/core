// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Event/CsTypes_StatusEffectEvent.h"
#pragma once

struct ICsStatusEffectEvent;
struct FCsResource_StatusEffectEvent;
class ICsStatusEffect;

/**
*/
struct CSSE_API FCsStatusEffectEventInfo
{
public:

	ICsStatusEffectEvent* Event;

	FCsResource_StatusEffectEvent* Container;

	FCsStatusEffectTriggerFrequencyInfo FrequencyInfo;

	float TotalTime;

	FCsDeltaTime ElapsedTotalTime;

	bool bDelayComplete;

	FCsDeltaTime ElapsedDelayTime;

	FCsDeltaTime ElapsedIntervalTime;

	int32 Count;

public:

	FCsStatusEffectEventInfo();

public:

	void SetEvent(FCsResource_StatusEffectEvent* InEvent);

	bool CanApply() const;

	void Increment();

	bool IsComplete() const;

	void Update(const FCsDeltaTime& DeltaTime);

	void Reset();
};