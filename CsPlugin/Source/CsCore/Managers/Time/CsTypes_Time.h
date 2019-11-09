// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
//#include "Types/CsTypes_Primitive.h"

//#include "CsTypes_Time.generated.h"
#pragma once

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