// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

struct CSCORE_API FCsVectorWithNormal2D
{
public:

	FVector3f Value;

private:

	FVector3f Normal;

	float Size;
	float SizeSq;

public:

	FORCEINLINE FCsVectorWithNormal2D() :
		Value(0.0f),
		Normal(0.0f),
		Size(0.0f),
		SizeSq(0.0f)
	{
	}

	FORCEINLINE const FVector3f& GetNormal() const { return Normal; }

	FORCEINLINE const float& GetSize() const { return Size; }
	FORCEINLINE const float& GetSizeSq() const { return SizeSq; }

	FORCEINLINE void ResolveNormal()
	{
		SizeSq = Value.X * Value.X + Value.Y * Value.Y;

		// Not sure if it's safe to add tolerance in there. Might introduce too many errors
		if (SizeSq == 1.0f)
		{
			Size = 1.0f;

			if (Value.Z == 0.f)
			{
				Normal = Value;
			}
			else
			{
				Normal = FVector3f(Value.X, Value.Y, 0.f);
			}
		}
		else
		if (SizeSq < SMALL_NUMBER)
		{
			Size   = 0.0f;
			Normal = FVector3f::ZeroVector;
		}
		else
		{
			Size   = FMath::Sqrt(SizeSq);
			Normal = (1.0f / Size) * FVector3f(Value.X, Value.Y, 0.f);
		}
	}

	FORCEINLINE void Limit(const float& Max)
	{
		if (Max == 0.0f)
		{
			Reset();
		}
		else
		{
			ResolveNormal();

			const float MaxSq = Max * Max;

			if (SizeSq > MaxSq)
			{
				Value  = Max * Normal;
				Size   = Max;
				SizeSq = MaxSq;
			}
		}
	}

	FORCEINLINE void Reset()
	{
		Value  = FVector3f::ZeroVector;
		Normal = FVector3f::ZeroVector;
		Size   = 0.0f;
		SizeSq = 0.0f;
	}
};