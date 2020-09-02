// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventInfo.h"
#include "CsSe.h"

// Status Effect
#include "Data/CsData_StatusEffect.h"
#include "Event/CsResource_StatusEffectEvent.h"

FCsStatusEffectEventInfo::FCsStatusEffectEventInfo() :
	Event(nullptr),
	Container(nullptr),
	FrequencyInfo(),
	TotalTime(0.0f),
	ElapsedTotalTime(),
	bDelayComplete(false),
	ElapsedDelayTime(),
	ElapsedIntervalTime(),
	Count(0)
{
}

void FCsStatusEffectEventInfo::SetEvent(FCsResource_StatusEffectEvent* InEvent)
{
	Container = InEvent;
	Event	  = Container->Get();

	ICsData_StatusEffect* Data = Event->GetData();

	FrequencyInfo.SetData(Data);
}

bool FCsStatusEffectEventInfo::CanApply() const
{
	return FrequencyInfo.CanApply();
}

void FCsStatusEffectEventInfo::Increment()
{
	FrequencyInfo.Increment();
}

bool FCsStatusEffectEventInfo::IsComplete() const
{
	return FrequencyInfo.IsComplete();
}

void FCsStatusEffectEventInfo::Update(const FCsDeltaTime& DeltaTime)
{
	FrequencyInfo.Update(DeltaTime);
}

void FCsStatusEffectEventInfo::Reset()
{
	Event = nullptr;
	Container = nullptr;
	FrequencyInfo.Reset();
}