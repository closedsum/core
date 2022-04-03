// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

struct CSCORE_API FCsVectorWithNormal2D
{
public:

	FVector Value;

private:

	FVector Normal;

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

	FORCEINLINE const FVector& GetNormal() const { return Normal; }

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
				Normal = FVector(Value.X, Value.Y, 0.f);
			}
		}
		else
		if (SizeSq < SMALL_NUMBER)
		{
			Size   = 0.0f;
			Normal = FVector::ZeroVector;
		}
		else
		{
			Size   = FMath::Sqrt(SizeSq);
			Normal = (1.0f / Size) * FVector(Value.X, Value.Y, 0.f);
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
		Value  = FVector::ZeroVector;
		Normal = FVector::ZeroVector;
		Size   = 0.0f;
		SizeSq = 0.0f;
	}
};