// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Event/CsTypes_StatusEffectEvent.h"
#pragma once

// NCsStatusEffect::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, IEvent)
// NCsStatusEffect::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, FResource)

class ICsStatusEffect;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NInfo
		{
			/**
			*/
			struct CSSE_API FImpl
			{
			private:

				typedef NCsStatusEffect::NEvent::FResource EventResourceType;

			public:

				IEvent* Event;

				EventResourceType* Container;

				FCsStatusEffectTriggerFrequencyInfo FrequencyInfo;

				float TotalTime;

				FCsDeltaTime ElapsedTotalTime;

				bool bDelayComplete;

				FCsDeltaTime ElapsedDelayTime;

				FCsDeltaTime ElapsedIntervalTime;

				int32 Count;

			public:

				FImpl();

			public:

				void SetEvent(EventResourceType* InEvent);

				bool CanApply() const;

				void Increment();

				bool IsComplete() const;

				void Update(const FCsDeltaTime& DeltaTime);

				void Reset();
			};
		}
	}
}