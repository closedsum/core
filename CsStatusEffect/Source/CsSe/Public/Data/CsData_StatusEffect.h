// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"
#include "CsTypes_StatusEffect.h"
#include "CsData_StatusEffect.generated.h"

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect : public ICsGetInterfaceMap
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
	virtual const FCsStatusEffectTransferFrequencyParams& GetTransferFrequencyParams() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const TArray<ICsData_StatusEffect*>& GetChildren() const = 0;
};