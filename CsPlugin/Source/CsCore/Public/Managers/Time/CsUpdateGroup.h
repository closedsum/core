// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"

//#include "CsUpdateGroup.generated.h"
#pragma once

struct CSCORE_API FCsUpdateGroup
{
private:

	/** Is the group paused. */
	bool bPause;

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPause, bool /*bPaused*/);

private:

	FOnPause OnPause_Event;

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

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdate, const FCsDeltaTime& /*DeltaTime*/);

private:

	FOnUpdate OnUpdate_Event;

	/** The time elapsed since the group as started. */
	FCsDeltaTime TimeSinceStart;

	/** The time elapsed since bPause was set to true. */
	FCsDeltaTime TimePaused;

	/** Whether group is being updated in a custom way. */
	bool bCustom;

	bool bClearCustomOnUpdate;

	/** Only Valid if bCustom == true. A specific DeltaTime to use
		when calling Update. */
	FCsDeltaTime CustomDeltaTime;

public:

	FCsUpdateGroup() :
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

		OnPause_Event.Broadcast(bPause);
	}

	FORCEINLINE void Unpause()
	{
		bPause = false;
		OnPause_Event.Broadcast(bPause);
	}

	FORCEINLINE bool IsPaused() const
	{
		return bPause;
	}

	FORCEINLINE FOnPause& GetOnPause_Event() { return OnPause_Event; }

	FORCEINLINE FDelegateHandle AddOnPause(FOnPause::FDelegate& OnPause)
	{
		return OnPause_Event.Add(OnPause);
	}

	FORCEINLINE void RemoveOnPause(const FDelegateHandle& Handle)
	{
		OnPause_Event.Remove(Handle);
	}

	FORCEINLINE void SetScale(const float& InScale)
	{
		Scale = InScale;
	}

	FORCEINLINE void ResetScale() { Scale = 1.0f; }

	void Update(const float& InDeltaTime)
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

	void Update(const float& InDeltaTime, const float& InTime, const float& InRealTime)
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

	FORCEINLINE FOnUpdate& GetOnUpdate_Event() { return OnUpdate_Event; }

	FORCEINLINE FDelegateHandle AddOnUpdate(FOnUpdate::FDelegate& OnUpdate)
	{
		return OnUpdate_Event.Add(OnUpdate);
	}

	FORCEINLINE void RemoveOnUpdate(const FDelegateHandle& Handle)
	{
		OnUpdate_Event.Remove(Handle);
	}

	FORCEINLINE const FCsTime& GetTime() const { return Time; }
	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime() const { return ScaledDeltaTime; }
	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FName& ScaleName) const { return ScaledDeltaTimes[ScaleName]; }
	FORCEINLINE const FCsDeltaTime& GetTimeSinceStart() const { return TimeSinceStart; }
	FORCEINLINE const FCsDeltaTime& GetTimePaused() const { return TimePaused; }

	FORCEINLINE void SetCustom(const bool& ClearOnUpdate = true) 
	{ 
		bCustom = true;
		bClearCustomOnUpdate = ClearOnUpdate;
	}
	FORCEINLINE void ClearCustom() 
	{ 
		bCustom = false;
		bClearCustomOnUpdate = true;
	}
	FORCEINLINE const bool& IsCustom() const { return bCustom; }

	FORCEINLINE void SetCustomDeltaTime(const FCsDeltaTime& InDeltaTime) { CustomDeltaTime = InDeltaTime; }
};