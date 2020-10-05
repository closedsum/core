// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventInfo.h"
#include "CsSe.h"

// Status Effect
#include "Data/CsData_StatusEffect.h"
#include "Event/CsResource_StatusEffectEvent.h"

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NInfo
		{
			FImpl::FImpl() :
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

			void FImpl::SetEvent(EventResourceType* InEvent)
			{
				Container = InEvent;
				Event = Container->Get();

				ICsData_StatusEffect* Data = Event->GetData();

				FrequencyInfo.SetData(Data);
			}

			bool FImpl::CanApply() const
			{
				return FrequencyInfo.CanApply();
			}

			void FImpl::Increment()
			{
				FrequencyInfo.Increment();
			}

			bool FImpl::IsComplete() const
			{
				return FrequencyInfo.IsComplete();
			}

			void FImpl::Update(const FCsDeltaTime& DeltaTime)
			{
				FrequencyInfo.Update(DeltaTime);
			}

			void FImpl::Reset()
			{
				Event = nullptr;
				Container = nullptr;
				FrequencyInfo.Reset();
			}
		}
	}
}