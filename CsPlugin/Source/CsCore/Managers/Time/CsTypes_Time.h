// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Time.generated.h"
#pragma once

// TimeGroup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsTimeGroup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsTimeGroup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsTimeGroup)

struct CSCORE_API EMCsTimeGroup final : public TCsEnumStructMap<FECsTimeGroup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsTimeGroup, FECsTimeGroup, uint8)
};

namespace NCsTimeGroup
{
	typedef FECsTimeGroup Type;

	extern CSCORE_API const Type GameInstance;
	extern CSCORE_API const Type GameState;
	extern CSCORE_API const Type Menu;
}

#pragma endregion TimeGroup

struct CSCORE_API FCsTime
{
public:

	float Time;
	float RealTime;
	FDateTime DateTime;
	uint64 Frame;

	FCsTime()
	{
		Reset();
	}
	~FCsTime() {}

	void Reset()
	{
		Time = 0.0f;
		RealTime = 0.0f;
		DateTime = FDateTime::Now();
		Frame = 0;
	}
};

struct CSCORE_API FCsDeltaTime
{
public:

	static const FCsDeltaTime Zero;

public:

	float Time;
	float RealTime;
	FTimespan Timespan;
	uint64 Frame;

	FCsDeltaTime()
	{
		Reset();
	}
	~FCsDeltaTime() {}

	FORCEINLINE FCsDeltaTime& operator+=(const FCsDeltaTime& B)
	{
		Time += B.Time;
		RealTime += B.RealTime;
		Timespan += B.Timespan;
		Frame += B.Frame;
		return *this;
	}
	
	/*
	FORCEINLINE friend FCsDeltaTime operator-(const FCsTime& A, const FCsTime& B)
	{
		FCsDeltaTime DeltaTime;
		DeltaTime.Time = A.Time - B.Time;
		DeltaTime.RealTime = A.RealTime - B.RealTime;
		DeltaTime.Timespan = A.Time - B.Time;
		DeltaTime.Frame = A.Frame - B.Frame;
		return DeltaTime;
	}
	*/
	void Reset()
	{
		Time = 0.0f;
		RealTime = 0.0f;
		Timespan = FTimespan::Zero();
		Frame = 0;
	}

	static FCsDeltaTime GetDeltaTime(const FCsTime& A, const FCsTime& B)
	{
		FCsDeltaTime DeltaTime;
		DeltaTime.Time = A.Time - B.Time;
		DeltaTime.RealTime = A.RealTime - B.RealTime;
		DeltaTime.Timespan = A.DateTime - B.DateTime;
		DeltaTime.Frame = A.Frame - B.Frame;
		return DeltaTime;
	}
};

struct CSCORE_API FCsTimeGroup
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

	FCsTimeGroup() :
		bPause(false),
		Scale(1.0f),
		StartTime(),
		LastTime(),
		Time(),
		DeltaTime(),
		ScaledDeltaTime()
	{
	}

	~FCsTimeGroup(){}

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