// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_StatusEffect.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"
#include "Data/Visual/FX/CsData_StatusEffect_VisualFX.h"

namespace NCsStatusEffect
{
	namespace NData
	{
	#define DataType NCsStatusEffect::NData::IData

		FString FLibrary::PrintDataAndClass(DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("Data: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
			return FString::Printf(TEXT("INVALID (Non-UObject)"));
		}

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data) 
		{ 
			CS_IS_PTR_NULL_CHECKED(Data)

			// Trigger
			typedef NCsStatusEffect::NData::NTrigger::ITrigger TriggerDataType;

			if (const TriggerDataType* TriggerData = GetSafeInterfaceChecked<TriggerDataType>(Context, Data))
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsStatusEffectTriggerCondition, TriggerData->GetTriggerCondition())
				CS_IS_VALID_CHECKED(TriggerData->GetTriggerFrequencyParams());
				CS_IS_VALID_CHECKED(TriggerData->GetTransferFrequencyParams());
			}

			// Visual FX
			typedef NCsStatusEffect::NData::NVisual::NFX::IFX VisualFXDataType;

			if (const VisualFXDataType* VisualFXData = GetSafeInterfaceChecked<VisualFXDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(VisualFXData->GetFX());
			}
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/) 
		{ 
			CS_IS_PTR_NULL(Data)

			// Trigger
			typedef NCsStatusEffect::NData::NTrigger::ITrigger TriggerDataType;

			if (const TriggerDataType* TriggerData = GetSafeInterfaceChecked<TriggerDataType>(Context, Data))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition, TriggerData->GetTriggerCondition())
				CS_IS_VALID(TriggerData->GetTriggerFrequencyParams())
				CS_IS_VALID(TriggerData->GetTransferFrequencyParams())
			}

			// Visual FX
			typedef NCsStatusEffect::NData::NVisual::NFX::IFX VisualFXDataType;

			if (const VisualFXDataType* VisualFXData = GetSafeInterfaceChecked<VisualFXDataType>(Context, Data))
			{
				CS_IS_VALID(VisualFXData->GetFX())
			}
			return true;
		}

	#undef DataType
	}
}