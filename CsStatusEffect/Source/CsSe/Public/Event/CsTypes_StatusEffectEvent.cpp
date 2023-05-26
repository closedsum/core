// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsTypes_StatusEffectEvent.h"

// Types
#include "Types/CsTypes_StatusEffect.h"
// Library
#include "Data/CsLibrary_Data_StatusEffect.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		namespace NFrequency
		{
			namespace NInfo
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NTrigger::NFrequency::FInfo, SetData);
					}
				}
			}

			#define DataType NCsStatusEffect::NData::IData
			void FInfo::SetData(DataType* InData)
			{
			#undef DataType
				
				using namespace NCsStatusEffect::NTrigger::NFrequency::NInfo::NCached;

				const FString& Context = Str::SetData;

				CS_IS_PTR_NULL_CHECKED(InData)

				Data = InData;

				typedef NCsStatusEffect::NData::FLibrary StatusEffectDataLibrary;
				typedef NCsStatusEffect::NData::NTrigger::ITrigger TriggerDataType;

				TriggerData = StatusEffectDataLibrary::GetInterfaceChecked<TriggerDataType>(Context, Data);

				typedef NCsStatusEffect::NTrigger::NFrequency::FParams TriggerFrequencyParamsType;

				const TriggerFrequencyParamsType& Params = TriggerData->GetTriggerFrequencyParams();

				typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

				const FrequencyType& Type = Params.GetType();

				bDelayComplete = Params.GetDelay() > 0.0f;

				// Once
				if (Type == FrequencyType::Once)
				{
					TotalTime = Params.GetDelay();
				}
				// Count
				else
				if (Type == FrequencyType::Count)
				{
					TotalTime += Params.GetDelay();
					TotalTime += Params.GetDelay() * Params.GetInterval();
				}
				// Time
				else
				if (Type == FrequencyType::Time)
				{
				}
			}

			bool FInfo::CanApply() const
			{
				typedef NCsStatusEffect::NTrigger::NFrequency::FParams TriggerFrequencyParamsType;

				const TriggerFrequencyParamsType& Params = TriggerData->GetTriggerFrequencyParams();

				typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

				const FrequencyType& Type = Params.GetType();

				// Once
				if (Type == FrequencyType::Once)
				{
					// Check Delay
					if (!bDelayComplete)
						return ElapsedDelayTime.Time >= Params.GetDelay();
					return ElapsedTotalTime.Time >= TotalTime;
				}
				// Count
				else
				if (Type == FrequencyType::Count)
				{
					// Check Delay
					if (!bDelayComplete)
						return ElapsedDelayTime.Time >= Params.GetDelay();
					// Check Interval
					if (Params.GetInterval() > 0.0f)
						return ElapsedIntervalTime.Time > Params.GetInterval();
					return true;
				}
				// Time
				else
				if (Type == FrequencyType::Time)
				{
					// Check Delay
					if (!bDelayComplete)
						return ElapsedDelayTime.Time >= Params.GetDelay();
					return ElapsedIntervalTime.Time > Params.GetInterval();
				}
				// Infinite
				else
				if (Type == FrequencyType::Infinite)
				{
					// Check Delay
					if (!bDelayComplete)
						return ElapsedDelayTime.Time >= Params.GetDelay();
					return ElapsedIntervalTime.Time > Params.GetInterval();
				}
				return false;
			}

			void FInfo::Increment()
			{
				bDelayComplete = true;
				ElapsedIntervalTime.Reset();
				++Count;
			}

			bool FInfo::IsComplete() const
			{
				typedef NCsStatusEffect::NTrigger::NFrequency::FParams TriggerFrequencyParamsType;

				const TriggerFrequencyParamsType& Params = TriggerData->GetTriggerFrequencyParams();

				typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

				const FrequencyType& Type = Params.GetType();

				// Once
				if (Type == FrequencyType::Once)
				{
					return ElapsedTotalTime.Time > TotalTime;
				}
				// Count
				else
				if (Type == FrequencyType::Count)
				{
					return Count >= Params.GetCount();
				}
				// Time
				else
				if (Type == FrequencyType::Time)
				{
					return ElapsedTotalTime.Time > TotalTime;
				}
				return false;
			}

			void FInfo::Update(const FCsDeltaTime& DeltaTime)
			{
				ElapsedTotalTime += DeltaTime;
				ElapsedDelayTime += DeltaTime;
				ElapsedIntervalTime += DeltaTime;
			}

			void FInfo::Reset()
			{
				Data = nullptr;
				TriggerData = nullptr;
				TotalTime = 0.0f;
				ElapsedTotalTime.Reset();
				ElapsedDelayTime.Reset();
				ElapsedIntervalTime.Reset();
				Count = 0;
			}
		}
	}
}