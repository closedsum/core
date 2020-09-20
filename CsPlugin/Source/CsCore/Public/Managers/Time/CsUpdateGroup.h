// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"

//#include "CsUpdateGroup.generated.h"
#pragma once

struct CSCORE_API FCsUpdateGroup
{
private:

	/** Is the group paused. */
	bool bPause;

	/** The current multiplier to delta time. Defaults to 1.0. */
	float Scale;

	/** A map of additional multipliers to delta time. These values are multiplied with Scale. */
	TMap<FName, float> Scales;

	/** The current time. */
	FCsTime StartTime;

	/** The time since Update was last called. */
	FCsTime LastTime;

	/** The time when Update was called. */
	FCsTime Time;

	/** The difference between Time and LastTime (Time - LastTime). */
	FCsDeltaTime DeltaTime;

	/** The scaled version of DeltaTime (Scale * DeltaTime). */
	FCsDeltaTime ScaledDeltaTime;

	/** The scaled version of DeltaTime for additional scales (Scale * Scales[Name] * DeltaTime). */
	TMap<FName, FCsDeltaTime> ScaledDeltaTimes;

	/** The time elapsed since the group as started. */
	FCsDeltaTime TimeSinceStart;

	/** The time elapsed since bPause was set to true. */
	FCsDeltaTime TimePaused;

public:

	FCsUpdateGroup() :
		bPause(false),
		Scale(1.0f),
		Scales(),
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
		TimePaused.Reset();
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
			// ScaledDeltaTimes
			for (TPair<FName, FCsDeltaTime>& Pair : ScaledDeltaTimes)
			{
				Pair.Value			 = ScaledDeltaTime;
				Pair.Value.Time		*= Scale;
				Pair.Value.RealTime *= Scale;
			}
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
			// ScaledDeltaTimes
			for (TPair<FName, FCsDeltaTime>& Pair : ScaledDeltaTimes)
			{
				Pair.Value			 = ScaledDeltaTime;
				Pair.Value.Time		*= Scale;
				Pair.Value.RealTime *= Scale;
			}
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

	FORCEINLINE const FCsTime& GetTime() const
	{
		return Time;
	}

	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime() const
	{
		return ScaledDeltaTime;
	}

	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FName& ScaleName) const
	{
		return ScaledDeltaTimes[ScaleName];
	}

	FORCEINLINE const FCsDeltaTime& GetTimeSinceStart() const
	{
		return TimeSinceStart;
	}

	FORCEINLINE const FCsDeltaTime& GetTimePaused() const
	{
		return TimePaused;
	}
};