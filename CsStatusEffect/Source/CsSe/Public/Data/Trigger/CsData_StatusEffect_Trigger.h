// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"
#include "Trigger/CsTypes_StatusEffect_Trigger.h"

#include "CsData_StatusEffect_Trigger.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NTrigger
		{
			/**
			*/
			struct CSSE_API ITrigger : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsStatusEffect::NTrigger::NFrequency::FParams TriggerFrequencyParamsType;
				typedef NCsStatusEffect::NTransfer::NFrequency::FParams TransferFrequencyParamsType;

			public:

				virtual ~ITrigger(){}

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
				virtual const TriggerFrequencyParamsType& GetTriggerFrequencyParams() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const TransferFrequencyParamsType& GetTransferFrequencyParams() const = 0;
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect_Trigger : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect_Trigger : public ICsGetInterfaceMap
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
	virtual const FCsStatusEffect_TriggerFrequencyParams& GetTriggerFrequencyParams() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FCsStatusEffect_TransferFrequencyParams& GetTransferFrequencyParams() const = 0;
};