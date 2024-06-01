// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsResourceSize.generated.h"

// FCsResourceSize
#pragma region

USTRUCT()
struct CSTYPES_API FCsResourceSize
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "CsTypes|Load")
	int32 Bytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsTypes|Load")
	float Kilobytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsTypes|Load")
	float Megabytes;

	FCsResourceSize()
	{
		Reset();
	}

	FORCEINLINE FCsResourceSize& operator=(const FCsResourceSize& B)
	{
		Bytes = B.Bytes;
		Kilobytes = B.Kilobytes;
		Megabytes = B.Megabytes;
		return *this;
	}

	FORCEINLINE FCsResourceSize& operator+=(const FCsResourceSize& B)
	{
		Bytes += B.Bytes;
		Kilobytes += B.Kilobytes;
		Megabytes += B.Megabytes;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsResourceSize& B) const
	{
		return Bytes == B.Bytes && Kilobytes == B.Kilobytes && Megabytes == B.Megabytes;
	}

	FORCEINLINE void Reset()
	{
		Bytes = 0;
		Kilobytes = 0.0f;
		Megabytes = 0.0f;
	}

	void SetBytes(const int32& InBytes)
	{
		Bytes	  = InBytes;
		Kilobytes = Bytes * FMath::Pow(10.0f, -3.0f);
		Megabytes = Bytes * FMath::Pow(10.0f, -6.0f);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%f mb, %f kb, %d b"), Megabytes, Kilobytes, Bytes);
	}
};

#pragma endregion FCsResourceSize