// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_Time.generated.h"
#pragma once

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTime
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	float Time;

	UPROPERTY(BlueprintReadOnly)
	float RealTime;

	UPROPERTY(BlueprintReadOnly)
	FDateTime DateTime;

	UPROPERTY()
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

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDeltaTime
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsDeltaTime Zero;

public:

	UPROPERTY(BlueprintReadOnly)
	float Time;

	UPROPERTY(BlueprintReadOnly)
	float RealTime;

	UPROPERTY(BlueprintReadOnly)
	FTimespan Timespan;

	UPROPERTY()
	uint64 Frame;

	FCsDeltaTime()
	{
		Reset();
	}
	~FCsDeltaTime() {}

	FORCEINLINE bool operator==(const FCsDeltaTime& B) const
	{
		return Time == B.Time && RealTime == B.RealTime && Timespan == B.Timespan && Frame == B.Frame;
	}

	FORCEINLINE bool operator!=(const FCsDeltaTime& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FCsDeltaTime& operator+=(const FCsDeltaTime& B)
	{
		Time += B.Time;
		RealTime += B.RealTime;
		Timespan += B.Timespan;
		Frame += B.Frame;
		return *this;
	}
	
	FORCEINLINE FCsDeltaTime operator+(const FCsDeltaTime& B) const
	{
		FCsDeltaTime A;
		A.Time	   = Time + B.Time;
		A.RealTime = RealTime + B.RealTime;
		A.Timespan = Timespan + B.Timespan;
		A.Frame	   = Frame + B.Frame;
		return A;
	}
	
	FORCEINLINE friend FCsDeltaTime operator-(const FCsDeltaTime& A, const FCsDeltaTime& B)
	{
		FCsDeltaTime DeltaTime;
		DeltaTime.Time = A.Time - B.Time;
		DeltaTime.RealTime = A.RealTime - B.RealTime;
		DeltaTime.Timespan = A.Timespan - B.Timespan;
		DeltaTime.Frame = A.Frame - B.Frame;
		return DeltaTime;
	}

	FORCEINLINE friend bool operator>(const FCsDeltaTime& A, const FCsDeltaTime& B)
	{
		return A.Time > B.Time || A.RealTime > B.RealTime || A.Timespan > B.Timespan || A.Frame > B.Frame;
	}

	FORCEINLINE friend bool operator>=(const FCsDeltaTime& A, const FCsDeltaTime& B)
	{
		return A.Time >= B.Time || A.RealTime >= B.RealTime || A.Timespan >= B.Timespan || A.Frame >= B.Frame;
	}

	FORCEINLINE friend bool operator<(const FCsDeltaTime& A, const FCsDeltaTime& B)
	{
		return A.Time < B.Time || A.RealTime < B.RealTime || A.Timespan < B.Timespan || A.Frame < B.Frame;
	}

	FORCEINLINE friend bool operator<=(const FCsDeltaTime& A, const FCsDeltaTime& B)
	{
		return A.Time <= B.Time || A.RealTime <= B.RealTime || A.Timespan <= B.Timespan || A.Frame <= B.Frame;
	}

	void Reset()
	{
		Time = 0.0f;
		RealTime = 0.0f;
		Timespan = FTimespan::Zero();
		Frame = 0;
	}

	FString ToCompactString() const
	{
		return FString::Printf(TEXT("Time: %3.3f RealTime: %3.3f Timespan: %s Frame: %lld"), Time, RealTime, *(Timespan.ToString()), Frame);
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