// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"
#include "CsTypes_StatusEffect.h"
#include "CsStatusEffect.generated.h"

UINTERFACE(Blueprintable)
class CSSE_API UCsStatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsStatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Get the trigger condition
	*
	* return Trigger Condition
	*/
	virtual const FECsStatusEffectTriggerCondition& GetTriggerCondition() const = 0;

	/**
	* Get the trigger frequency.
	* If GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Once,
	*  Ignore GetCount() and GetInterval().
	* If GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Count,
	*  GetCount() should be > 0, if NOT, it will be treated
	*  as ECsStatusEffectTriggerFrequency::Once.
	* If GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Infinite,
	*  Ignore GetCount() and GetInterval() should be > 0.0f.
	* 
	* return Trigger Type
	*/
	virtual const ECsStatusEffectTriggerFrequency& GetTriggerFrequency() const = 0;

	/**
	* Get the number of times to apply the status effect when triggered.
	* Only valid if GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Count.
	* Should be > 0.
	*
	* return Count
	*/
	virtual const int32& GetCount() const = 0;

	/**
	* Get the delay before applying the status effect when triggered.
	* If Delay == 0.0f, the status effect will be applied at a given interval.
	* If Delay == 0.0f and Interval == 0.0f, the status will be applied immediately.
	*
	* return Delay
	*/
	virtual const float& GetDelay() const = 0;

	/**
	* Get the time between each status effect being applied when triggered.
	* Only valid if, 
	*  GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Count 
	*  or
	*  GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Infinite 
	*
	* return Interval
	*/
	virtual const float& GetInterval() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const TArray<ICsStatusEffect*>& GetChildren() const = 0;
};