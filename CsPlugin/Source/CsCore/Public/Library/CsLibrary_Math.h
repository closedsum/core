// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Interpolation.h"

/**
*/
class CSCORE_API FCsLibrary_Math
{
public:

	FORCEINLINE static float BytesToKilobytes(const int32& Bytes)
	{
		return Bytes * FMath::Pow(10, -3);
	}

	FORCEINLINE static float BytesToMegabytes(const int32& Bytes)
	{
		return Bytes * FMath::Pow(10, -6);
	}

	FORCEINLINE static int32 KilobytesToBytes(const float& Kilobytes)
	{
		return Kilobytes * FMath::Pow(10, 3);
	}

// Easing
#pragma region
public:

	static float Ease(const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration);
	
	FORCEINLINE static float Linear(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		return ((Final * Time) / Duration) + Start;
	}

	// Bounce

	FORCEINLINE static float BounceEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		float T = Time;

		T /= Duration;

		if (T < (1 / 2.75f))
		{
			return Final * (7.5625f * T * T) + Start;
		}
		else if (Time < (2.0f / 2.75f))
		{
			T -= (1.5f / 2.75f);
			return Final * (7.5625f * T * T + 0.75f) + Start;
		}
		else if (Time < (2.5f / 2.75f))
		{
			T -= (2.25f / 2.75f);
			return Final * (7.5625f * T * T + 0.9375f) + Start;
		}
		else
		{
			T -= (2.625f / 2.75f);
			return Final * (7.5625f * T * T + 0.984375f) + Start;
		}
	}

	FORCEINLINE static float BounceEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		return Final - BounceEaseOut(Duration - Time, 0, Final, Duration) + Start;
	}

	FORCEINLINE static float BounceEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		if (Time < (Duration / 2.0f))
			return (BounceEaseIn(Time * 2, 0, Final, Duration) * 0.5f) + Start;
		else
			return (BounceEaseOut(Time * 2 - Duration, 0, Final, Duration) * 0.5f) + Final * 0.5f + Start;
	}

	// Sinusoidal

	/** Sinusoidal in interpolation. */
	//SinusoidalIn,
	/** Sinusoidal out interpolation. */
	//SinusoidalOut,
	/** Sinusoidal in/out interpolation. */
	//SinusoidalInOut,
	
	// Ease

	/** Smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by BlendExp. */
	//EaseIn,
	/** Immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by BlendExp. */
	//EaseOut,
	/** Smoothly accelerates and decelerates.  Ease amount controlled by BlendExp. */
	//EaseInOut,

	// Cubic

	FORCEINLINE static float CubicEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		float T = Time;
		T /= Duration;
		return Final * T * T * T + Start;
	}

	FORCEINLINE static float CubicEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		float T = Time;
		T = (T / Duration) - 1.0f;
		return Final * ((T *  T * T) + 1) + Start;
	}

	FORCEINLINE static float CubicEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		float T = Time;

		if ((T / (Duration / 2.0f)) < 1)
		{
			T /= Duration / 2.0f;
			return (Final / (2.0f * T * T * T)) + Start;
		}
		T -= 2.0f;
		return (Final / (2 * T * T * T + 2)) + Start;
	}

	// Expo

	FORCEINLINE static float ExpoEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		return (Time == 0.0f) ? Start : Final * FMath::Pow(2.0f, 10.0f * (Time / Duration - 1.0f)) + Start;
	}

	FORCEINLINE static float ExpoEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		return (Time == Duration) ? Start + Final : Final * (-1.0f * FMath::Pow(2.0f, -10.0f * Time / Duration) + 1.0f) + Start;
	}

	FORCEINLINE static float ExpoEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		float T = Time;

		if (T == 0)
			return Start;
		if (T == Duration)
			return Start + Final;
		if (Duration / 2.0f < 1.0f)
		{
			T /= Duration / 2.0f;
			return (Final / 2.0f) * FMath::Pow(2.0f, 10 * (T - 1.0f)) + Start;
		}
		T--;
		return (Final / 2.0f) * (-FMath::Pow(2.0f, -10.0f * T) + 2.0f) + Start;
	}

	// Circ

	/** Easing is based on a half circle. */
	//CircularIn,
	/** Easing is based on an inverted half circle. */
	//CircularOut,
	/** Easing is based on two half circles. */
	//CircularInOut,

	static TCsEasingFunction GetEasingFunction(const ECsEasingType& EasingType);

	// Get Alpha

	FORCEINLINE static float Linear_GetAlpha(const float& Value, const float& Start, const float& Final, const float& Duration)
	{
		return (Duration * (Value - Start)) / Final;
	}
	
	// TODO: Need LoopUp Table

	/*
	FORCEINLINE static float BounceEaseOut_GetAlpha(const float& Value, const float& Start, const float& Final, const float& Duration)
	{
	}
	*/

	/*
	template< class T >
	static FORCEINLINE_DEBUGGABLE T InterpSinIn(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = -1.f * Cos(Alpha * HALF_PI) + 1.f;
		return Lerp<T>(A, B, ModifiedAlpha);
	}
	*/
#pragma endregion Easing

	FORCEINLINE static int32 Mod(const int32& A, const int32& B)
	{
		const int32 C = A % B;
		return C < 0 ? C + B : C;
	}
};