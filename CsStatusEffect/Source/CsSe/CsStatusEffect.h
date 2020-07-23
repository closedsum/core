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
	* Get the trigger frequency params. This describes the frequency the status effect is
	* triggered.
	*
	* return Trigger Frequency Params
	*/
	virtual const FCsStatusEffectTriggerFrequencyParams& GetTriggerFrequencyParams() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const TArray<ICsStatusEffect*>& GetChildren() const = 0;
};