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
		FInfo::FInfo() :
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

		void FInfo::SetEvent(FCsResource_StatusEffectEvent* InEvent)
		{
			Container = InEvent;
			Event	  = Container->Get();

			ICsData_StatusEffect* Data = Event->GetData();

			FrequencyInfo.SetData(Data);
		}

		bool FInfo::CanApply() const
		{
			return FrequencyInfo.CanApply();
		}

		void FInfo::Increment()
		{
			FrequencyInfo.Increment();
		}

		bool FInfo::IsComplete() const
		{
			return FrequencyInfo.IsComplete();
		}

		void FInfo::Update(const FCsDeltaTime& DeltaTime)
		{
			FrequencyInfo.Update(DeltaTime);
		}

		void FInfo::Reset()
		{
			Event = nullptr;
			Container = nullptr;
			FrequencyInfo.Reset();
		}
	}
}