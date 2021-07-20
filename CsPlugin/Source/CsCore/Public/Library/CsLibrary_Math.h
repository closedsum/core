// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Interpolation.h"

/**
*/
namespace NCsMath
{
	struct CSCORE_API FLibrary final
	{
	// Abs
	#pragma region
	public:

		FORCEINLINE static uint64 GetAbsDelta(const uint64& A, const uint64& B)
		{
			return A > B ? A - B : B - A;
		}

	#pragma endregion Abs

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

	// Vector
	#pragma region
	public:
		
		/**
		* Mostly copied from:  Core\Public\Math\Vector.h
		* 
		* Gets a normalized copy of the vector, checking it is safe to do so based on the length.
		* Returns zero vector if vector length is too small to safely normalize.
		*
		* @param V					The vector to the the normal for.
		* @param OutSizeSquared		V.SizeSquared().
		* @param OutSize			V.Size().
		* @param Tolerance			Minimum squared vector length.
		* @return					A normalized copy if safe, (0,0,0) otherwise.
		*/
		FORCEINLINE static FVector GetSafeNormal(const FVector& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			OutSizeSquared = V.X*V.X + V.Y*V.Y + V.Z*V.Z;

			// Not sure if it's safe to add tolerance in there. Might introduce too many errors
			if(OutSizeSquared == 1.0f)
			{
				OutSize = 1.0f;
				return V;
			}		
			else 
			if (OutSizeSquared < Tolerance)
			{
				OutSize = 0.0f;
				return FVector::ZeroVector;
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return (1.0f / OutSize) * V;
		}

		/**
		* Mostly copied from:  Core\Public\Math\Vector.h
		*
		* Gets a normalized copy of the vector, checking it is safe to do so based on the length.
		* Returns zero vector if vector length is too small to safely normalize.
		*
		* @param V					The vector to the the normal for.
		* @param OutSizeSquared		V.SizeSquared().
		* @param OutSize			V.Size().
		* @param Tolerance			Minimum squared vector length.
		* @return					A normalized copy if safe, (0,0,0) otherwise.
		*/
		FORCEINLINE static FVector GetSafeNormal2D(const FVector& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			OutSizeSquared = V.X*V.X + V.Y *V.Y;

			// Not sure if it's safe to add tolerance in there. Might introduce too many errors
			if (OutSizeSquared == 1.f)
			{
				if (V.Z == 0.f)
				{
					return V;
				}
				else
				{
					return FVector(V.X, V.Y, 0.f);
				}
			}
			else if (OutSizeSquared < Tolerance)
			{
				return FVector::ZeroVector;
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return (1.0f / OutSize) * V;
		}

		/**
		* Mostly copied from:  Core\Public\Math\Vector.h
		* 
		* Gets a normalized copy of the vector, checking it is safe to do so based on the length.
		* Returns zero vector if vector length is too small to safely normalize.
		*
		* @param V					The vector to the the normal for.
		* @param OutSizeSquared		V.SizeSquared().
		* @param OutSize			V.Size().
		* @param Tolerance			Minimum squared vector length.
		* @return					A normalized copy if safe, (0,0,0) otherwise.
		*/
		FORCEINLINE static FVector4 GetSafeNormal(const FVector4& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			OutSizeSquared = V.X*V.X + V.Y*V.Y + V.Z*V.Z + V.W*V.W;

			// Not sure if it's safe to add tolerance in there. Might introduce too many errors
			if(OutSizeSquared == 1.0f)
			{
				OutSize = 1.0f;
				return V;
			}		
			else 
			if (OutSizeSquared < Tolerance)
			{
				OutSize = 0.0f;
				return FVector4(0.0f);
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return OutSize * V;
		}

	#pragma endregion Vector

	// Plane
	#pragma region
	public:

		static bool IsValidChecked(const FString& Context, const FPlane& Plane);

		static bool IsValid(const FString& Context, const FPlane& Plane, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Plane

	// Intersection
	#pragma region
	public:

		/**
		* Computes the intersection point between a ray and a plane.
		* 
		* @param Context			The calling context.
		* @param Ray				The t of the intersection between the line and the plane.
		* @param Plane
		* @param OutT				(out)
		* @param OutIntersection	(out) The point of intersection between the line and the plane.
		* return					True if the intersection test was successful.
		*/
		static bool RayPlaneIntersectionChecked(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection);

		/**
		* Computes the intersection point between a ray and a plane.
		*
		* @param Context			The calling context.
		* @param Ray				The t of the intersection between the line and the plane.
		* @param Plane
		* @param OutT				(out)
		* @param OutIntersection	(out) The point of intersection between the line and the plane.
		* @param Log
		* return					True if the intersection test was successful.
		*/
		static bool SafeRayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Intersection

	// LinearColor
	#pragma region
	public:

		/**
		* Mostly copied from:  Core\Public\Math\Vector.h
		* 
		* Gets a "normalized" copy of the linear color, checking it is safe to do so based on the length.
		* Returns "zero" (clear) linear color if linear color's "length" is too small to safely normalize.
		*
		* @param Color				The color to get the "normal" for.
		* @param OutSizeSquared		Equivalent to FVector4::SizeSquared().
		* @param OutSize			Equivlanet to FVector4::Size().
		* @param Tolerance			Minimum squared linear color "length".
		* @return					A normalized copy if safe, (0.0f, 0.0f, 0.0f, 0.0f) otherwise.
		*/
		FORCEINLINE static FLinearColor GetSafeNormal(const FLinearColor& Color, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			return FLinearColor(GetSafeNormal(FVector4(Color), OutSizeSquared, OutSize, Tolerance));
		}

	#pragma endregion LinearColor
	};
}