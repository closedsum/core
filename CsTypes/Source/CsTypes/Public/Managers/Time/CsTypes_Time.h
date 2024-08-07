// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

#include "CsTypes_Time.generated.h"

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsTime
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsTime Zero;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	float RealTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	FDateTime DateTime;

	UPROPERTY()
	uint64 Frame;

	FCsTime() :
		Time(0.0f),
		RealTime(0.0f),
		DateTime(),
		Frame(0ull)
	{
		DateTime = FDateTime::Now();
	}

	void Reset()
	{
		Time = 0.0f;
		RealTime = 0.0f;
		DateTime = FDateTime::Now();
		Frame = 0;
	}

	FString ToCompactString() const
	{
		return FString::Printf(TEXT("Time: %3.3f RealTime: %3.3f DateTime: %s Frame: %lld"), Time, RealTime, *(DateTime.ToString()), Frame);
	}
};

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsDeltaTime
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsDeltaTime Zero;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	float RealTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Time")
	FTimespan Timespan;

	UPROPERTY()
	uint64 Frame;

	FCsDeltaTime() :
		Time(0.0f),
		RealTime(0.0f),
		Timespan(),
		Frame(0ull)
	{
		Timespan = FTimespan::Zero();
	}

	FCsDeltaTime(const float& InTime) :
		RealTime(0.0f),
		Timespan(),
		Frame(0ull)
	{
		Time = InTime;
		Timespan = FTimespan::Zero();
	}

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

	void Scale(const float& Scalar)
	{
		checkf(Scalar > 0.0f, TEXT("FCsDeltaTime::Scale: Scalar: %f is NOT Valid. Scalar MUST be > 0.0f."), Scalar);

		Time	 *= Scalar;
		RealTime *= Scalar;
		Timespan *= Scalar;
		// TODO: Frame
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