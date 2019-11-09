// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"

//#include "CsUpdateGroup.generated.h"
#pragma once

struct CSCORE_API FCsUpdateGroup
{
private:

	bool bPause;

	float Scale;

	FCsTime StartTime;

	FCsTime LastTime;

	FCsTime Time;

	FCsDeltaTime DeltaTime;

	FCsDeltaTime ScaledDeltaTime;

	FCsDeltaTime TimeSinceStart;

	FCsDeltaTime TimePaused;

public:

	FCsUpdateGroup() :
		bPause(false),
		Scale(1.0f),
		StartTime(),
		LastTime(),
		Time(),
		DeltaTime(),
		ScaledDeltaTime()
	{
	}

	~FCsUpdateGroup(){}

	void Start()
	{
		StartTime.DateTime = FDateTime::Now();
	}

	void Pause()
	{
		bPause = true;

		DeltaTime.Reset();
		ScaledDeltaTime.Reset();
	}

	void Unpause()
	{
		bPause = false;
	}

	FORCEINLINE bool IsPaused() const
	{
		return bPause;
	}

	void Update(const float& InDeltaTime)
	{
		Time.DateTime = FDateTime::Now();
		++(Time.Frame);

		if (!bPause)
		{
			// DeltaTime
			DeltaTime.Time		= InDeltaTime;
			DeltaTime.Timespan	= Time.DateTime - LastTime.DateTime;
			DeltaTime.RealTime	= (float)DeltaTime.Timespan.GetTotalSeconds();
			DeltaTime.Frame		= Time.Frame - LastTime.Frame;
			// ScaledDeltaTime
			ScaledDeltaTime			 = DeltaTime;
			ScaledDeltaTime.Time	 = Scale * DeltaTime.Time;
			ScaledDeltaTime.RealTime = Scale * DeltaTime.RealTime;
		}
		else
		{
			TimePaused.Time		+= InDeltaTime;
			TimePaused.Timespan += Time.DateTime - LastTime.DateTime;
			TimePaused.RealTime  = (float)TimePaused.Timespan.GetTotalSeconds();
			TimePaused.Frame	+= Time.Frame - LastTime.Frame;
		}

		TimeSinceStart.Time     += InDeltaTime;
		TimeSinceStart.Timespan += Time.DateTime - LastTime.DateTime;
		TimeSinceStart.RealTime  = (float)TimeSinceStart.Timespan.GetTotalSeconds();
		TimeSinceStart.Frame    += Time.Frame - LastTime.Frame;

		LastTime = Time;
	}

	void Update(const float& InDeltaTime, const float& InTime, const float& InRealTime)
	{
		Time.Time	  = InTime;
		Time.RealTime = InRealTime;
		Time.DateTime = FDateTime::Now();
		++(Time.Frame);

		if (!bPause)
		{
			// DeltaTime
			DeltaTime.Time	   = InDeltaTime;
			DeltaTime.Timespan = Time.DateTime - LastTime.DateTime;
			DeltaTime.RealTime = LastTime.RealTime - Time.RealTime;
			DeltaTime.Frame	   = Time.Frame - LastTime.Frame;
			// ScaledDeltaTime
			ScaledDeltaTime			 = DeltaTime;
			ScaledDeltaTime.Time	 = Scale * DeltaTime.Time;
			ScaledDeltaTime.RealTime = Scale * DeltaTime.RealTime;
		}
		else
		{
			TimePaused.Time		+= InDeltaTime;
			TimePaused.Timespan += Time.DateTime - LastTime.DateTime;
			TimePaused.RealTime  = InRealTime;
			TimePaused.Frame	+= Time.Frame - LastTime.Frame;
		}

		TimeSinceStart.Time		+= InDeltaTime;
		TimeSinceStart.Timespan += Time.DateTime - LastTime.DateTime;
		TimeSinceStart.RealTime += InRealTime;
		TimeSinceStart.Frame	+= Time.Frame - LastTime.Frame;

		LastTime = Time;
	}

	FORCEINLINE const FCsTime& GetTime()
	{
		return Time;
	}

	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime()
	{
		return ScaledDeltaTime;
	}

	FORCEINLINE const FCsDeltaTime& GetTimeSinceStart()
	{
		return TimeSinceStart;
	}

	FORCEINLINE const FCsDeltaTime& GetTimePaused()
	{
		return TimePaused;
	}
};