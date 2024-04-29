// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsUpdateGroup.h"

FCsUpdateGroup::FCsUpdateGroup() :
	bPause(false),
	OnPause_Event(),
	Scale(1.0f),
	Scales(),
	StartTime(),
	LastTime(),
	Time(),
	DeltaTime(),
	ScaledDeltaTime(),
	ScaledDeltaTimes(),
	OnUpdate_Event(),
	TimeSinceStart(),
	TimePaused(),
	bCustom(false),
	bClearCustomOnUpdate(true),
	CustomDeltaTime()
{
}

FCsUpdateGroup::~FCsUpdateGroup(){}

void FCsUpdateGroup::Update(const float& InDeltaTime)
{
	Time.DateTime = FDateTime::Now();
	++(Time.Frame);

	if (!bPause ||
		bCustom)
	{
		// DeltaTime
		DeltaTime.Time		= bCustom ? CustomDeltaTime.Time : InDeltaTime;
		DeltaTime.Timespan	= Time.DateTime - LastTime.DateTime;
		DeltaTime.RealTime	= (float)DeltaTime.Timespan.GetTotalSeconds();
		DeltaTime.Frame		= Time.Frame - LastTime.Frame;
		// ScaledDeltaTime
		ScaledDeltaTime			 = DeltaTime;
		ScaledDeltaTime.Time	 = Scale * DeltaTime.Time;
		ScaledDeltaTime.RealTime = Scale * DeltaTime.RealTime;
		// ScaledDeltaTimes
		for (TPair<FName, FCsDeltaTime>& Pair : ScaledDeltaTimes)
		{
			Pair.Value			 = ScaledDeltaTime;
			Pair.Value.Time		*= Scale;
			Pair.Value.RealTime *= Scale;
		}

		TimeSinceStart.Time     += bCustom ? CustomDeltaTime.Time : InDeltaTime;
		TimeSinceStart.Timespan += Time.DateTime - LastTime.DateTime;
		TimeSinceStart.RealTime  = (float)TimeSinceStart.Timespan.GetTotalSeconds();
		TimeSinceStart.Frame    += Time.Frame - LastTime.Frame;
	}
	else
	{
		TimePaused.Time		+= InDeltaTime;
		TimePaused.Timespan += Time.DateTime - LastTime.DateTime;
		TimePaused.RealTime  = (float)TimePaused.Timespan.GetTotalSeconds();
		TimePaused.Frame	+= Time.Frame - LastTime.Frame;
	}

	// NOTE: For now clear bCustom. bCustom has only been used to "manually" update
	//		 when paused. 
	// TODO: Consider renaming bCustom so its clearer whats going on.
	bCustom = !bClearCustomOnUpdate;

	LastTime = Time;

	OnUpdate_Event.Broadcast(ScaledDeltaTime);
}

void FCsUpdateGroup::Update(const float& InDeltaTime, const float& InTime, const float& InRealTime)
{
	Time.Time	  = InTime;
	Time.RealTime = InRealTime;
	Time.DateTime = FDateTime::Now();
	++(Time.Frame);

	if (!bPause ||
		bCustom)
	{
		// DeltaTime
		DeltaTime.Time	   = bCustom ? CustomDeltaTime.Time : InDeltaTime;
		DeltaTime.Timespan = Time.DateTime - LastTime.DateTime;
		DeltaTime.RealTime = LastTime.RealTime - Time.RealTime;
		DeltaTime.Frame	   = Time.Frame - LastTime.Frame;
		// ScaledDeltaTime
		ScaledDeltaTime			 = DeltaTime;
		ScaledDeltaTime.Time	 = Scale * DeltaTime.Time;
		ScaledDeltaTime.RealTime = Scale * DeltaTime.RealTime;
		// ScaledDeltaTimes
		for (TPair<FName, FCsDeltaTime>& Pair : ScaledDeltaTimes)
		{
			Pair.Value			 = ScaledDeltaTime;
			Pair.Value.Time		*= Scale;
			Pair.Value.RealTime *= Scale;
		}

		TimeSinceStart.Time		+= bCustom ? CustomDeltaTime.Time : InDeltaTime;
		TimeSinceStart.Timespan += Time.DateTime - LastTime.DateTime;
		TimeSinceStart.RealTime += InRealTime;
		TimeSinceStart.Frame	+= Time.Frame - LastTime.Frame;
	}
	else
	{
		TimePaused.Time		+= InDeltaTime;
		TimePaused.Timespan += Time.DateTime - LastTime.DateTime;
		TimePaused.RealTime  = InRealTime;
		TimePaused.Frame	+= Time.Frame - LastTime.Frame;
	}

	// NOTE: For now clear bCustom. bCustom has only been used to "manually" update
	//		 when paused. 
	// TODO: Consider renaming bCustom so its clearer whats going on.
	bCustom = !bClearCustomOnUpdate;

	LastTime = Time;

	OnUpdate_Event.Broadcast(ScaledDeltaTime);
}