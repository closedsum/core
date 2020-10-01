// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Event/CsTypes_StatusEffectEvent.h"
#pragma once

namespace NCsStatusEffect {
	namespace NEvent {
		struct IEvent; } }

struct FCsResource_StatusEffectEvent;
class ICsStatusEffect;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		/**
		*/
		struct CSSE_API FInfo
		{
		public:

			IEvent* Event;

			FCsResource_StatusEffectEvent* Container;

			FCsStatusEffectTriggerFrequencyInfo FrequencyInfo;

			float TotalTime;

			FCsDeltaTime ElapsedTotalTime;

			bool bDelayComplete;

			FCsDeltaTime ElapsedDelayTime;

			FCsDeltaTime ElapsedIntervalTime;

			int32 Count;

		public:

			FInfo();

		public:

			void SetEvent(FCsResource_StatusEffectEvent* InEvent);

			bool CanApply() const;

			void Increment();

			bool IsComplete() const;

			void Update(const FCsDeltaTime& DeltaTime);

			void Reset();
		};
	}
}