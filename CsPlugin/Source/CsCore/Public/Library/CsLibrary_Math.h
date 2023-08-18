// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Interpolation.h"

/**
*/
namespace NCsMath
{
	struct CSCORE_API FLibrary final
	{
	public:

		static FORCEINLINE FString GetFloatAsStringWithPrecision(const float& TheFloat, const uint8& Precision)
		{
			const TCHAR* TheDot = TEXT(".");

			FString FloatString = FString::SanitizeFloat(TheFloat);

			//No . ?
			if (!FloatString.Contains(TheDot))
			{
				return FloatString;
			}

			//Split
			FString LeftS;
			FString RightS;

			FloatString.Split(TheDot, &LeftS, &RightS);

			if (Precision == 0)
				return LeftS;

			//Add dot back to LeftS
			LeftS += TheDot;

			//Get the Single Number after the precision amount
			// so in .1273, get the 7
			FString RightSFirstTruncated = "";
			if (RightS.Len() - 1 >= Precision)
			{
				RightSFirstTruncated = RightS.Mid(Precision, 1);
			}

			//Truncate the RightS
			// 	.1273 becomes .12 with precision 2
			RightS = RightS.Left(Precision);

			//Round Up if There was any truncated portion
			if (RightSFirstTruncated != "")
			{
				if (FCString::Atod(*RightSFirstTruncated) >= 5)
				{
					//.1273 becomes .13
					RightS = FString::FromInt(FCString::Atod(*RightS) + 1);
				}
			}

			return LeftS + RightS;
		}

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
			return Bytes * FMath::Pow(10.0f, -3.0f);
		}

		FORCEINLINE static float BytesToMegabytes(const int32& Bytes)
		{
			return Bytes * FMath::Pow(10.0f, -6.0f);
		}

		FORCEINLINE static int32 KilobytesToBytes(const float& Kilobytes)
		{
			return Kilobytes * FMath::Pow(10.0f, 3.0f);
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

		FORCEINLINE static float Ease_BounceOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

		FORCEINLINE static float Ease_BounceIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			return Final - Ease_BounceOut(Duration - Time, 0, Final, Duration) + Start;
		}

		FORCEINLINE static float Ease_BounceInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			if (Time < (Duration / 2.0f))
				return (Ease_BounceIn(Time * 2, 0, Final, Duration) * 0.5f) + Start;
			else
				return (Ease_BounceOut(Time * 2 - Duration, 0, Final, Duration) * 0.5f) + Final * 0.5f + Start;
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

		// Quad
		
		FORCEINLINE static float Ease_QuadIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time;
			T /= Duration;
			return Final * T * T + Start;
		}

		FORCEINLINE static float Ease_QuadOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time;
			T /= Duration;
			return Final * (1.0f - (1.0f - T) * (1.0f - T)) + Start;
		}

		FORCEINLINE static float Ease_QuadInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time;
			T /= Duration;
			return T < 0.5f ? 2.0f * T * T : 1.0f - 0.5f *FMath::Pow((-2.0f * + T) + 2.0f, 2.0f);
		}

		// Cubic

		FORCEINLINE static float Ease_CubicIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time;
			T /= Duration;
			return Final * T * T * T + Start;
		}

		FORCEINLINE static float Ease_CubicOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time;
			T = (T / Duration) - 1.0f;
			return Final * ((T *  T * T) + 1) + Start;
		}

		FORCEINLINE static float Ease_CubicInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

		FORCEINLINE static float Ease_ExpoIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			return (Time == 0.0f) ? Start : Final * FMath::Pow(2.0f, 10.0f * (Time / Duration - 1.0f)) + Start;
		}

		FORCEINLINE static float Ease_ExpoOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			return (Time == Duration) ? Start + Final : Final * (-1.0f * FMath::Pow(2.0f, -10.0f * Time / Duration) + 1.0f) + Start;
		}

		FORCEINLINE static float Ease_ExpoInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

		// Back

		FORCEINLINE static float Ease_BackIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time / Duration;

			const float C1 = 1.70158f;
			const float C3 = C1 + 1.0f;

			return Final * ((C3 * T * T * T) - (C1 * T * T)) + Start;
		}

		FORCEINLINE static float Ease_BackOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = (Time / Duration) - 1.0f;

			const float C1 = 1.70158f;
			const float C3 = C1 + 1.0f;

			return Final * (1.0f + (C3 * T * T * T) + (C1 * T * T)) + Start;
		}

		FORCEINLINE static float Ease_BackInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time / Duration;

			const float C1 = 1.70158f;
			const float C2 = C1 * 1.525f;

			if (T < 0.5f)
			{
				T *= 2.0f;
				return 0.5f * (Final * (T * T + (((C2 + 1.0f) * T) - C2)) + Start);
			}
			T *= 2.0f;
			T -= 2.0f;
			return 0.5f * (Final * (T * T + (((C2 + 1.0f) * T) + C2 + 2.0f)) + Start);
		}

		// Elastic

		FORCEINLINE static float Ease_ElasticIn(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time / Duration;

			const float C4 = (2.0f * PI) / 3;

			if (T == 0.0f)
				return Start;
			if (T == 1.0f)
				return Final + Start;
			T *= 10.0f;
			return Final * (-FMath::Pow(2.0f, T - 10.0f) * FMath::Sin((T - 10.75f) * C4)) + Start;
		}

		FORCEINLINE static float Ease_ElasticOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time / Duration;

			const float C4 = (2.0f * PI) / 3;

			if (T == 0.0f)
				return Start;
			if (T == 1.0f)
				return Final + Start;
			T *= 10.0f;
			return Final * (FMath::Pow(2.0f, -T) * FMath::Sin((T - 0.75f) * C4) + 1.0f) + Start;
		}

		FORCEINLINE static float Ease_ElasticInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
		{
			float T = Time / Duration;

			const float C5 = (2.0f * PI) / 4.5;

			if (T == 0.0f)
				return Start;
			if (T == 1.0f)
				return Final + Start;
			if (T < 0.5f)
			{
				T *= 2.0f;
				return Final * (-0.5f * (FMath::Pow(2.0f, T - 10.0f) * FMath::Sin((T - 11.125f) * C5))) + Start;
			}
			T *= 2.0f;
			return Final * (0.5f * (FMath::Pow(2.0f, -T + 10.0f) * FMath::Sin((T - 11.125) * C5)) + 1.0f) + Start;
		}

		static TCsEasingFunction GetEasingFunction(const ECsEasingType& EasingType);

		// Get Alpha

		FORCEINLINE static float Linear_GetAlpha(const float& Value, const float& Start, const float& Final, const float& Duration)
		{
			return (Duration * (Value - Start)) / Final;
		}
	
		// TODO: Need LoopUp Table

		/*
		FORCEINLINE static float Ease_BounceOut_GetAlpha(const float& Value, const float& Start, const float& Final, const float& Duration)
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

	// Bezier
	#pragma region
	public:

		FORCEINLINE static float Bezier_Quadratic_GetArcLength(const float& T, const FVector3f& P0, const FVector3f& P1, const FVector3f& P2)
		{
			float ax, ay, bx, by, az, bz, A, B, C, b, c, u, k, L;
			ax = P0.X - P1.X - P1.X + P2.X;
			ay = P0.Y - P1.Y - P1.Y + P2.Y;
			az = P0.Z - P1.Z - P1.Z + P2.Z;
			bx = P1.X + P1.X - P0.X - P0.X;
			by = P1.Y + P1.Y - P0.Y - P0.Y;
			bz = P1.Z + P1.Z - P0.Z - P0.Z;
			A = 4.0f * ((ax * ax) + (ay * ay) + (az * az));
			B = 4.0f * ((ax * bx) + (ay * by) + (az * bz));
			C = (bx * bx) + (by * by) + (bz * bz);
			b = B / (2.0f * A);
			c = C / A;
			u = T + b;
			k = c - (b * b);
			L = 0.5f * FMath::Sqrt(A) *
				((u * FMath::Sqrt((u * u) + k)) - (b * FMath::Sqrt((b * b) + k)) +
				 (k * FMath::Loge(FMath::Abs((u + FMath::Sqrt((u * u) + k)) / (b + FMath::Sqrt((b * b) + k))))));
			return L;
		}

	#pragma endregion Bezier

		FORCEINLINE static int32 Mod(const int32& A, const int32& B)
		{
			const int32 C = A % B;
			return C < 0 ? C + B : C;
		}

		FORCEINLINE static int32 Sign(const float& F)
		{
			{return 1 + (((*(int32*)&F) >> 31) << 1); }
		}

	// Angle
	#pragma region
	public:

		FORCEINLINE static float GetAngleDelta(const float& Angle1, const float& Angle2)
		{
			const int32 Mag		   = Angle2 - Angle1 > 0 ? 1 : -1;
			const float DeltaAngle = Angle2 - Angle1;

			return FMath::Abs(DeltaAngle) > 180.0f ? -1 * Mag * (360.0f - FMath::Abs(DeltaAngle)) : Mag * FMath::Abs(DeltaAngle);
		}

		FORCEINLINE static FRotator3f GetAngleDelta(const FRotator3f& A, const FRotator3f& B)
		{
			FRotator3f Rotation;

			Rotation.Pitch = GetAngleDelta(A.Pitch, B.Pitch);
			Rotation.Yaw   = GetAngleDelta(A.Yaw, B.Yaw);
			Rotation.Roll  = GetAngleDelta(A.Roll, B.Roll);

			return Rotation;
		}
	
		FORCEINLINE static float GetAbsAngleDelta(const float& Angle1, const float& Angle2)
		{
			const float DeltaAngle = Angle2 - Angle1;
			const int32 Mag		   = DeltaAngle > 0 ? 1 : -1;

			return FMath::Abs(FMath::Abs(DeltaAngle) > 180.0f ? -1 * Mag * (360.0f - FMath::Abs(DeltaAngle)) : Mag * FMath::Abs(DeltaAngle));
		}

		FORCEINLINE static FRotator3f GetAbsAngleDelta(const FRotator3f& A, const FRotator3f& B)
		{
			FRotator3f Rotation;

			Rotation.Pitch = GetAbsAngleDelta(A.Pitch, B.Pitch);
			Rotation.Yaw   = GetAbsAngleDelta(A.Yaw, B.Yaw);
			Rotation.Roll  = GetAbsAngleDelta(A.Roll, B.Roll);

			return Rotation;
		}

		FORCEINLINE static float AngleClamp180(float Angle)
		{
			while (Angle < -180.0f) { Angle += 360.0f; }
			while (Angle > 180.0f) { Angle -= 360.0f; }
			return Angle;
		}

		FORCEINLINE static FRotator3f AngleClamp180(const FRotator3f& Rotation)
		{
			return FRotator3f(AngleClamp180(Rotation.Pitch), AngleClamp180(Rotation.Yaw), AngleClamp180(Rotation.Roll));
		}

		FORCEINLINE static float AngleClamp360(float Angle)
		{
			Angle = FMath::Fmod(Angle, 360.0f);

			if (Angle < 0.0f)
				Angle += 360.0f;
			return Angle;
		}

		FORCEINLINE static FRotator3f AngleClamp360(const FRotator3f& Rotation)
		{
			return FRotator3f(AngleClamp360(Rotation.Pitch), AngleClamp360(Rotation.Yaw), AngleClamp360(Rotation.Roll));
		}

		FORCEINLINE static float AngleClampTwoPI(float Angle)
		{
			Angle = FMath::Fmod(Angle, 2.0f * PI);

			if (Angle < 0.0f)
				Angle += 2.0f * PI;
			return Angle;
		}

		FORCEINLINE static float LerpAngle(const float& Angle1, const float& Angle2, const float& Rate, const float& DeltaTime)
		{
			const int32 Mag		   = Angle2 - Angle1 > 0 ? 1 : -1;
			const float DeltaAngle = Angle2 - Angle1;
			const float Direction  = FMath::Abs(DeltaAngle) > 180.0f ? -Mag : Mag;

			if (Direction > 0.0f)
				return FMath::Min(DeltaTime * Rate + Angle1, Angle2);
			if (Direction < 0.0f)
				return FMath::Max(-1.0f * DeltaTime * Rate + Angle1, Angle2);
			return Angle2;
		}

	#pragma endregion Angle

	// Vector
	#pragma region
	public:
		
		FORCEINLINE static void Set(FVector3f& To, const FVector3d& From)
		{
			To.X = (float)From.X;
			To.Y = (float)From.Y;
			To.Z = (float)From.Z;
		}

		FORCEINLINE static FVector2f Convert(const FVector2d& V) { return FVector2f((float)V.X, (float)V.Y); }
		FORCEINLINE static FVector2d Convert(const FVector2f& V) { return FVector2d((double)V.X, (double)V.Y); }

		FORCEINLINE static FVector3f Convert(const FVector3d& V) { return FVector3f((float)V.X, (float)V.Y, (float)V.Z); }
		FORCEINLINE static FVector3d Convert(const FVector3f& V) { return FVector3d((double)V.X, (double)V.Y, (double)V.Z); }

		FORCEINLINE static FVector4f Convert(const FVector4d& V) { return FVector4f((float)V.X, (float)V.Y, (float)V.Z, (float)V.W); }
		FORCEINLINE static FVector4d Convert(const FVector4f& V) { return FVector4d((double)V.X, (double)V.Y, (double)V.Z, (double)V.W); }

		/**
		* Mostly copied from:  Core\Public\Math\Vector2D.h
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
		FORCEINLINE static FVector2f GetSafeNormal(const FVector2f& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			OutSizeSquared = V.X*V.X + V.Y*V.Y;

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
				return FVector2f(0.0f);
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
		FORCEINLINE static FVector3f GetSafeNormal(const FVector3f& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
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
				return FVector3f::ZeroVector;
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
		FORCEINLINE static FVector3d GetSafeNormal(const FVector3d& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
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
				return FVector3d::ZeroVector;
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
		FORCEINLINE static FVector3f GetSafeNormal2D(const FVector3f& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
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
					return FVector3f(V.X, V.Y, 0.f);
				}
			}
			else if (OutSizeSquared < Tolerance)
			{
				return FVector3f::ZeroVector;
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return (1.0f / OutSize) * FVector3f(V.X, V.Y, 0.f);
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
		FORCEINLINE static FVector3d GetSafeNormal2D(const FVector3d& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			OutSizeSquared = V.X*V.X + V.Y *V.Y;

			// Not sure if it's safe to add tolerance in there. Might introduce too many errors
			if (OutSizeSquared == 1.f)
			{
				if (V.Z == 0.0)
				{
					return V;
				}
				else
				{
					return FVector3d(V.X, V.Y, 0.0);
				}
			}
			else if (OutSizeSquared < Tolerance)
			{
				return FVector3d::ZeroVector;
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return (1.0f / OutSize) * FVector3d(V.X, V.Y, 0.0);
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
		FORCEINLINE static FVector4f GetSafeNormal(const FVector4f& V, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
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
				return FVector4f(0.0f);
			}

			OutSize = FMath::Sqrt(OutSizeSquared);

			return OutSize * V;
		}

		/**
		* Call V.Rotation() and return the rotation with ONLY the Yaw value as
		* Yaw + Offset.
		* 
		* @param V
		* @param Offset		Value to be added to V.Rotation().Yaw.
		* return			FRotator3f(0.0f, V.Rotation().Yaw + Offset, 0.0f).
		*/
		FORCEINLINE static FRotator3f ToRotatorOnlyYaw(const FVector3f& V, const float& Offset = 0.0f)
		{
			FRotator3f R = FRotator3f::ZeroRotator;

			R.Yaw = FMath::Atan2(V.Y, V.X) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (R.ContainsNaN())
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::ToRotatorOnlyYaw(): Rotator result %s contains NaN! Input FVector3f = %s"), *(R.ToString()), *(V.ToString()));
				R = FRotator3f::ZeroRotator;
			}
#endif
			R.Yaw += Offset;

			return R;
		}

		/**
		* Call V.Rotation() and return the Yaw.
		*
		* @param V
		* return	V.Rotation().Yaw.
		*/
		FORCEINLINE static float GetYaw(const FVector3f& V)
		{
			const float Yaw = FMath::Atan2(V.Y, V.X) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (!FMath::IsFinite(Yaw))
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::GetYaw(): Yaw result %f contains NaN! Input FVector3f = %s"), Yaw, *(V.ToString()));
				return 0.0f;
			}
#endif
			return Yaw;
		}

		/**
		* Call V.Rotation() and return the rotation with ONLY the Pitch value as
		* Pitch + Offset.
		*
		* @param V
		* @param Offset		Value to be added to V.Rotation().Pitch.
		* return			FRotator3f(0.0f, V.Rotation().Pitch + Offset, 0.0f).
		*/
		FORCEINLINE static FRotator3f ToRotatorOnlyPitch(const FVector3f& V, const float& Offset = 0.0f)
		{
			FRotator3f R = FRotator3f::ZeroRotator;

			R.Pitch = FMath::Atan2(V.Z, FMath::Sqrt((V.X * V.X) + (V.Y * V.Y))) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (R.ContainsNaN())
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::ToRotatorOnlyYaw(): Rotator result %s contains NaN! Input FVector3f = %s"), *(R.ToString()), *(V.ToString()));
				R = FRotator3f::ZeroRotator;
			}
#endif
			R.Yaw += Offset;

			return R;
		}

		/**
		* Call V.Rotation() and return the Pitch.
		*
		* @param V
		* return	V.Rotation().Pitch.
		*/
		FORCEINLINE static float GetPitch(const FVector3f& V)
		{
			const float Pitch = FMath::Atan2(V.Z, FMath::Sqrt((V.X * V.X) + (V.Y * V.Y))) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (!FMath::IsFinite(Pitch))
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::GetPitch(): Pitch result %f contains NaN! Input FVector3f = %s"), Pitch, *(V.ToString()));
				return 0.0f;
			}
#endif
			return Pitch;
		}

		FORCEINLINE static bool IsAnyComponentZero(const FVector3f& V) { return V.X == 0.0f || V.Y == 0.0f || V.Z == 0.0f; }
		FORCEINLINE static bool IsAnyComponentZero(const FVector3d& V) { return V.X == 0.0 || V.Y == 0.0 || V.Z == 0.0; }

		FORCEINLINE static FVector3f Limit2D(const FVector3f& V, const float& Max)
		{
			if (Max == 0.0f)
				return FVector3f::ZeroVector;

			const float DSq = V.SizeSquared2D();
			
			if (DSq < SMALL_NUMBER)
				return V;

			if (DSq > (Max * Max))
			{
				return (Max / DSq) * V;
			}
			return V;
		}

		FORCEINLINE static FVector3f GetUpFromNormal(const FVector3f& N) { return GetUp(N.Rotation()); }
		FORCEINLINE static FVector3f GetUp(const FVector3f& V) { return GetUpFromNormal(V.GetSafeNormal()); }

		FORCEINLINE static FVector3f GetRightFromNormal(const FVector3f& N) { return GetRight(N.Rotation()); }
		FORCEINLINE static FVector3f GetRight(const FVector3f& V) { return GetRightFromNormal(V.GetSafeNormal()); }
		FORCEINLINE static FVector3f GetRightFromNormal2D(const FVector3f& N) { return GetRightOnlyYaw(GetYaw(N)); }
		FORCEINLINE static FVector3f GetRightFromNormal2D(const FVector3f& N, float& OutYaw) 
		{
			OutYaw = GetYaw(N);
			return GetRightOnlyYaw(OutYaw);
		}
		FORCEINLINE static FVector3f GetRightFromNormal2D(const FVector3f& N, FRotator3f& OutRotation)
		{
			OutRotation.Yaw = GetYaw(N);
			return GetRightOnlyYaw(OutRotation.Yaw);
		}

		FORCEINLINE static void GetRightAndUpFromNormal(const FVector3f& N, FVector3f& OutRight, FVector3f& OutUp) { GetRightAndUp(N.Rotation(), OutRight, OutUp); }

		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of the 'Up' vector relative to N.
		* 
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Up' vector relative to N.
		*/
		FORCEINLINE static FVector3f RotateNormalAngleUp(const FVector3f& N, const float& Angle) { return N.RotateAngleAxis(Angle, GetUpFromNormal(N)); }
		
		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of World Up (FVector3f::UpVector).
		*
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Up' vector relative to N.
		*/
		FORCEINLINE static FVector3f RotateNormalWorldUp(const FVector3f& N, const float& Angle) { return N.RotateAngleAxis(Angle, FVector3f::UpVector); }

		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of the 'Right' vector relative to N.
		*
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Right' vector relative to N.
		*/
		FORCEINLINE static FVector3f RotateNormalAngleRight(const FVector3f& N, const float& Angle) { return N.RotateAngleAxis(Angle, GetRightFromNormal(N));  }

		FORCEINLINE static FVector3f Fractional(const FVector3f& V)
		{
			return FVector3f(FMath::Fractional(V.X), FMath::Fractional(V.Y), FMath::Fractional(V.Z));
		}

		FORCEINLINE static float DotProduct2D(const FVector3f& A, const FVector3f& B)
		{
			return A.X * B.X + A.Y * B.Y;
		}

		FORCEINLINE static FVector3f Multiply(const FVector3f& V, const FQuat4f& Quat)
		{
			const FVector3f QuatXYZ = FVector3f(Quat.X, Quat.Y, Quat.Z);

			const FVector3f Part1 = 2.0f * FVector3f::DotProduct(QuatXYZ, V) * QuatXYZ;
			const FVector3f Part2 = (FMath::Square(Quat.W) - FVector3f::DotProduct(QuatXYZ, QuatXYZ)) * V;
			const FVector3f Part3 = 2.0f * Quat.W * FVector3f::CrossProduct(QuatXYZ, V);

			const FVector3f Vector = Part1 + Part2 + Part3;
			return Vector;
		}

		FORCEINLINE static FVector3f RandRange(const FVector3f& Min, const FVector3f& Max)
		{
			return FVector3f(FMath::RandRange(Min.X, Max.X), FMath::RandRange(Min.Y, Max.Y), FMath::RandRange(Min.Z, Max.Z));
		}

		FORCEINLINE static float GetAbsMax(const FVector4f& V)
		{
			return FMath::Max(FMath::Max(FMath::Max(FMath::Abs(V.X), FMath::Abs(V.Y)), FMath::Abs(V.Z)), FMath::Abs(V.W));
		}

		/**
		* Interpolate a normal vector Current to Target, by interpolating the angle between those vectors with constant step. 
		*/
		FORCEINLINE static FVector3f VInterpNormalRotationTo(const FVector3f& Current, const FVector3f& Target, float DeltaTime, float RotationSpeedDegrees)
		{
			// Find delta rotation between both normals.
			FQuat4f DeltaQuat = FQuat4f::FindBetween(Current, Target);

			// Decompose into an axis and angle for rotation
			FVector3f DeltaAxis(0.f);
			FQuat4f::FReal DeltaAngle = 0.f;
			DeltaQuat.ToAxisAndAngle(DeltaAxis, DeltaAngle);

			// Find rotation step for this frame
			const float RotationStepRadians = RotationSpeedDegrees * (UE_PI / 180) * DeltaTime;

			if (FMath::Abs(DeltaAngle) > RotationStepRadians)
			{
				DeltaAngle = FMath::Clamp<FQuat4f::FReal>(DeltaAngle, -RotationStepRadians, RotationStepRadians);
				DeltaQuat = FQuat4f(DeltaAxis, DeltaAngle);
				return DeltaQuat.RotateVector(Current);
			}
			return Target;
		}

		/** 
		* Interpolate vector from Current to Target with constant step 
		*/
		FORCEINLINE static FVector3f VInterpConstantTo(const FVector3f& Current, const FVector3f& Target, const float& DeltaTime, const float& InterpSpeed)
		{
			const FVector3f Delta		   = Target - Current;
			const FVector3f::FReal DeltaM  = Delta.Size();
			const FVector3f::FReal MaxStep = InterpSpeed * DeltaTime;

			if (DeltaM > MaxStep)
			{
				if (MaxStep > 0.f)
				{
					const FVector3f DeltaN = Delta / DeltaM;
					return Current + DeltaN * MaxStep;
				}
				else
				{
					return Current;
				}
			}
			return Target;
		}

	#pragma endregion Vector

	// Rotator
	#pragma region
	public:

		FORCEINLINE static FRotator3f Convert(const FRotator3d& R) { return FRotator3f((float)R.Pitch, (float)R.Yaw, (float)R.Roll); }
		FORCEINLINE static FRotator3d Convert(const FRotator3f& R) { return FRotator3d((double)R.Pitch, (double)R.Yaw, (double)R.Roll); }

		FORCEINLINE static FVector3f GetForwardOnlyYaw(const FRotator3f& R) { return GetForward3fOnlyYaw(R.Yaw); }
		FORCEINLINE static FVector3d GetForwardOnlyYaw(const FRotator3d& R) { return GetForward3dOnlyYaw(R.Yaw); }
		FORCEINLINE static FVector3f GetForward3fOnlyYaw(const FRotator3d& R) { return GetForward3fOnlyYaw((float)R.Yaw); }
		FORCEINLINE static FVector3f GetForward3fOnlyYaw(const float& Yaw)
		{
			const float Y = FMath::Fmod(Yaw, 360.0f);

			float SY, CY;
			FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Y));

			return FVector3f(CY, SY, 0.0f);
		}
		FORCEINLINE static FVector3d GetForward3dOnlyYaw(const FRotator3f& R) { return GetForward3dOnlyYaw((double)R.Yaw); }
		FORCEINLINE static FVector3d GetForward3dOnlyYaw(const double& Yaw)
		{
			const double Y = FMath::Fmod(Yaw, 360.0);

			double SY, CY;
			FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Y));

			return FVector3d(CY, SY, 0.0);
		}

		FORCEINLINE static FVector3f GetRight(const FRotator3f& R) { return FRotationMatrix44f(R).GetScaledAxis(EAxis::Y); }
		FORCEINLINE static FVector3f GetRightOnlyYaw(const float& Yaw)
		{
			const float Y = FMath::Fmod(Yaw, 360.0f);

			float SY, CY;
			FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Y));

			return FVector3f(-SY, CY, 0.0f);
		}
		FORCEINLINE static FVector3f GetRightOnlyYaw(const FRotator3f& R)
		{
			return GetRightOnlyYaw(R.Yaw);
		}

		FORCEINLINE static FVector3f GetUp(const FRotator3f& R) { return FRotationMatrix44f(R).GetScaledAxis(EAxis::Z); }

		FORCEINLINE static void GetForwardRightAndUp(const FRotator3f& R, FVector3f& OutForward, FVector3f& OutRight, FVector3f& OutUp)
		{
			FRotationMatrix44f M(R);
			OutForward = M.GetScaledAxis(EAxis::X);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

		FORCEINLINE static void GetRightAndUp(const FRotator3f& R, FVector3f& OutRight, FVector3f& OutUp)
		{
			FRotationMatrix44f M(R);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

		/** 
		* Find a rotation for an object at Start location to point at Target location.
		*/
		FORCEINLINE static FRotator3f FindLookAtRotation(const FVector3f& Start, const FVector3f& Target)
		{
			return FRotationMatrix44f::MakeFromX(Target - Start).Rotator();
		}

	#pragma endregion Rotator

	// Quat
	#pragma region
	public:

		FORCEINLINE static FQuat4f Convert(const FQuat4d& Q) { return FQuat4f((float)Q.X, (float)Q.Y, (float)Q.Z, (float)Q.W); }
		FORCEINLINE static FQuat4d Convert(const FQuat4f& Q) { return FQuat4d((double)Q.X, (double)Q.Y, (double)Q.Z, (double)Q.W); }

		FORCEINLINE static FVector3f GetRight(const FQuat4f& Q) { return GetRight(Q.Rotator()); }
		FORCEINLINE static FVector3f GetUp(const FQuat4f& Q) { return GetUp(Q.Rotator()); }

		FORCEINLINE static void GetForwardRightAndUp(const FQuat4f& Q, FVector3f& OutForward, FVector3f& OutRight, FVector3f& OutUp)
		{
			FMatrix44f M = FRotationMatrix44f::Make(Q);
			OutForward = M.GetScaledAxis(EAxis::X);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

		FORCEINLINE static void RotateByPitch(FQuat4f& OutQ, float Radians)
		{
			const FQuat4f DeltaQuat = FQuat4f(FVector3f::RightVector, Radians);
			OutQ				 *= DeltaQuat;
			OutQ.Normalize();
		}

		FORCEINLINE static FQuat4f RotateByPitch(const FQuat4f& Q, float Radians)
		{
			FQuat4f NewQuat = Q;
			RotateByPitch(NewQuat, Radians);
			return NewQuat;
		}

		FORCEINLINE static void RotateByPitchDegrees(FQuat4f& OutQ, float Degrees) { RotateByPitch(OutQ, FMath::DegreesToRadians(Degrees)); }
		FORCEINLINE static FQuat4f RotateByPitchDegrees(const FQuat4f& Q, float Degrees) { return RotateByPitch(Q, FMath::DegreesToRadians(Degrees)); }
		
		FORCEINLINE static void RotateByRoll(FQuat4f& OutQ, float Radians)
		{
			const FQuat4f DeltaQuat = FQuat4f(FVector3f::ForwardVector, Radians);
			OutQ *= DeltaQuat;
			OutQ.Normalize();
		}

		FORCEINLINE static FQuat4f RotateByRoll(const FQuat4f& Q, float Radians)
		{
			FQuat4f NewQuat = Q;
			RotateByRoll(NewQuat, Radians);
			return NewQuat;
		}

		FORCEINLINE static void RotateByRollDegrees(FQuat4f& OutQ, float Degrees) { RotateByRoll(OutQ, FMath::DegreesToRadians(Degrees)); }
		FORCEINLINE static FQuat4f RotateByRollDegrees(const FQuat4f& Q, float Degrees) { return RotateByRoll(Q, FMath::DegreesToRadians(Degrees)); }

		FORCEINLINE static void RotateByYaw(FQuat4f& OutQ, float Radians)
		{
			const FQuat4f DeltaQuat = FQuat4f(FVector3f::UpVector, Radians);
			OutQ *= DeltaQuat;
			OutQ.Normalize();
		}

		FORCEINLINE static FQuat4f RotateByYaw(const FQuat4f& Q, float Radians)
		{
			FQuat4f NewQuat = Q;
			RotateByRoll(NewQuat, Radians);
			return NewQuat;
		}

		FORCEINLINE static void RotateByYawDegrees(FQuat4f& OutQ, float Degrees) { RotateByYaw(OutQ, FMath::DegreesToRadians(Degrees)); }
		FORCEINLINE static FQuat4f RotateByYawDegrees(const FQuat4f& Q, float Degrees) { return RotateByYaw(Q, FMath::DegreesToRadians(Degrees)); }

	#pragma endregion Quat

	// Transform
	#pragma region
	public:

		FORCEINLINE static FTransform3f Convert(const FTransform3d& T) 
		{
			FTransform3f Transform;
			Transform.SetTranslation(Convert(T.GetTranslation()));
			Transform.SetRotation(Convert(T.GetRotation()));
			Transform.SetScale3D(Convert(T.GetScale3D()));

			return Transform;
		}

		FORCEINLINE static FTransform3d Convert(const FTransform3f& T)
		{
			FTransform3d Transform;
			Transform.SetTranslation(Convert(T.GetTranslation()));
			Transform.SetRotation(Convert(T.GetRotation()));
			Transform.SetScale3D(Convert(T.GetScale3D()));

			return Transform;
		}

	#pragma endregion Transform

	// Matrix
	#pragma region
	public:

		FORCEINLINE static FMatrix44f Convert(const FMatrix44d& M) 
		{
			FMatrix44f Mf;
			Mf.M[0][0] = (float)M.M[0][0]; Mf.M[0][1] = (float)M.M[0][1]; Mf.M[0][2] = (float)M.M[0][2]; Mf.M[0][3] = (float)M.M[0][3];
			Mf.M[1][0] = (float)M.M[1][0]; Mf.M[1][1] = (float)M.M[1][1]; Mf.M[1][2] = (float)M.M[1][2]; Mf.M[1][3] = (float)M.M[1][3];
			Mf.M[2][0] = (float)M.M[2][0]; Mf.M[2][1] = (float)M.M[2][1]; Mf.M[2][2] = (float)M.M[2][2]; Mf.M[2][3] = (float)M.M[2][3];
			Mf.M[3][0] = (float)M.M[3][0]; Mf.M[3][1] = (float)M.M[3][1]; Mf.M[3][2] = (float)M.M[3][2]; Mf.M[3][3] = (float)M.M[3][3];
			return Mf;
		}
		FORCEINLINE static FMatrix44d Convert(const FMatrix44f& M)
		{
			FMatrix44d Md;
			Md.M[0][0] = (double)M.M[0][0]; Md.M[0][1] = (double)M.M[0][1]; Md.M[0][2] = (double)M.M[0][2]; Md.M[0][3] = (double)M.M[0][3];
			Md.M[1][0] = (double)M.M[1][0]; Md.M[1][1] = (double)M.M[1][1]; Md.M[1][2] = (double)M.M[1][2]; Md.M[1][3] = (double)M.M[1][3];
			Md.M[2][0] = (double)M.M[2][0]; Md.M[2][1] = (double)M.M[2][1]; Md.M[2][2] = (double)M.M[2][2]; Md.M[2][3] = (double)M.M[2][3];
			Md.M[3][0] = (double)M.M[3][0]; Md.M[3][1] = (double)M.M[3][1]; Md.M[3][2] = (double)M.M[3][2]; Md.M[3][3] = (double)M.M[3][3];
			return Md;
		}

	#pragma endregion Matrix

	// Segment
	#pragma region
	public:

		/**
		* Returns closest point on a segment to a given point.
		* The idea is to project point on line formed by segment.
		* Then we see if the closest point on the line is outside of segment or inside.
		*
		* @param Point			point for which we find the closest point on the segment
		* @param StartPoint		StartPoint of segment
		* @param EndPoint		EndPoint of segment
		* @param OutT			(out) Percentage the closest point lies between StartPoint (0.0f) and EndPoint (1.0f).
		* return				point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
		*/
		static FVector3f ClosestPointOnSegment(const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT);

		/**
		* Returns closest point on a segment to a given point.
		* The idea is to project point on line formed by segment.
		* Then we see if the closest point on the line is outside of segment or inside.
		*
		* @param Context		The calling context.
		* @param Point			point for which we find the closest point on the segment
		* @param StartPoint		StartPoint of segment
		* @param EndPoint		EndPoint of segment
		* @param OutT			(out) Percentage the closest point lies between StartPoint (0.0f) and EndPoint (1.0f).
		* return				point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
		*/
		static FVector3f ClosestPointOnSegmentChecked(const FString& Context, const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT);

		/**
		* Safely returns closest point on a segment to a given point.
		* The idea is to project point on line formed by segment.
		* Then we see if the closest point on the line is outside of segment or inside.
		*
		* @param Context		The calling context.
		* @param Point			point for which we find the closest point on the segment
		* @param StartPoint		StartPoint of segment
		* @param EndPoint		EndPoint of segment
		* @param OutT			(out) Percentage the closest point lies between StartPoint (0.0f) and EndPoint (1.0f).
		* @param Log			(optional)
		* return				point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
		*/
		static FVector3f SafeClosestPointOnSegment(const FString& Context, const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Segment

	// Plane
	#pragma region
	public:

		FORCEINLINE static FPlane4f Convert(const FPlane4d& Plane) { return FPlane4f((float)Plane.X, (float)Plane.Y, (float)Plane.Z, (float)Plane.W); }
		FORCEINLINE static FPlane4d Convert(const FPlane4f& Plane) { return FPlane4d((double)Plane.X, (double)Plane.Y, (double)Plane.Z, (double)Plane.W); }

		static bool IsValidChecked(const FString& Context, const FPlane4f& Plane);

		static bool IsValid(const FString& Context, const FPlane4f& Plane, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static bool RayPlaneIntersectionChecked(const FString& Context, const FCsRay& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection);

		/**
		* returns the time (t) of the intersection of the passed segment and a plane (could be <0 or >1)
		* @param StartPoint - start point of segment
		* @param EndPoint   - end point of segment
		* @param Plane		- plane to intersect with
		* @return time(T) of intersection
		*/
		FORCEINLINE static float GetTForSegmentPlaneIntersect(const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane)
		{
			return FMath::GetTForSegmentPlaneIntersect(Convert(StartPoint), Convert(EndPoint), Convert(Plane));
		}

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
		static bool SafeRayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* a Plane If there is an intersection, the point is placed in OutIntersectPoint
		*
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param Plane				
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* return					True if intersection occurred
		*/
		static bool SegmentPlaneIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint);

		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* a Plane If there is an intersection, the point is placed in OutIntersectPoint
		*
		* @param Context			The calling context.
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param Plane
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* return					True if intersection occurred
		*/
		static bool SegmentPlaneIntersectionChecked(const FString& Context, const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint);

		/**
		* Safely returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* a Plane If there is an intersection, the point is placed in OutIntersectPoint
		*
		* @param Context			The calling context.
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param Plane
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* @param Log				(optional)
		* return					True if intersection occurred
		*/
		static bool SafeSegmentPlaneIntersection(const FString& Context, const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* the Quad defined by A, B, C, and D. If there is an intersection, the point is placed in OutIntersectPoint.
		* NOTE: FUTURE: Improve
		*  Quad Layout
		*  
		*  B ---- C
		*  |	  |
		*  |      |
		*  A ---- D
		* 
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param A, B, C, D			Points defining the quad
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* @param OutNormal			(out) var for the quad normal
		* @return					True if intersection occurred
		*/
		static bool SegmentQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, float& OutT, FVector3f& OutIntersectPoint, FVector3f& OutNormal);

		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* the Quad defined by A, B, C, and D. If there is an intersection, the point is placed in OutIntersectPoint.
		* NOTE: FUTURE: Improve
		*  Quad Layout
		*  
		*  B ---- C
		*  |	  |
		*  |      |
		*  A ---- D
		* 
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param A, B, C, D			Points defining the quad
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* @param OutNormal			(out) var for the quad normal
		* @param OutUV				(out) Percentage OutIntersectPoint lies in the U (AB) and V (AD).
		* @return					True if intersection occurred
		*/
		static bool SegmentRectangleQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, float& OutT, FVector3f& OutIntersectPoint, FVector3f& OutNormal, FVector2f& OutUV);

		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* the Quad defined by A, B, C, and D. If there is an intersection, the point is placed in OutIntersectPoint.
		* NOTE: FUTURE: Improve
		*  Quad Layout
		*
		*  B ---- C
		*  |	  |
		*  |      |
		*  A ---- D
		*
		* @param StartPoint			Start point of segment
		* @param EndPoint			End point of segment
		* @param A, B, C, D			Points defining the quad
		* @param Plane
		* @param Normal
		* @param InvArea
		* @param OutT				(out)
		* @param OutIntersectPoint	(out) var for the point on the segment that intersects the triangle (if any)
		* @param OutUV				(out) Percentage OutIntersectPoint lies in the U (AB) and V (AD).
		* @return					True if intersection occurred
		*/
		static bool SegmentRectangleQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, const FPlane4f& Plane, const FVector3f& ABC_Normal, const float& ABC_InvArea, const FVector3f& ADC_Normal, const float& ADC_InvArea, float& OutT, FVector3f& OutIntersectPoint, FVector2f& OutUV);

	#pragma endregion Intersection

	// Triangle
	#pragma region
	public:

		/**
		* Computes the barycentric coordinates for a given point in a triangle
		*
		* @param	Point			point to convert to barycentric coordinates (in plane of ABC)
		* @param	A,B,C			three non-collinear points defining a triangle in CCW
		*
		* @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
		*							                               or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
		*/
		FORCEINLINE static FVector3f ComputeBaryCentric2D(const FVector3f& Point, const FVector3f& A, const FVector3f& B, const FVector3f& C)
		{
			return Convert(FMath::ComputeBaryCentric2D(Convert(Point), Convert(A), Convert(B), Convert(C)));
		}

		/**
		* Computes the barycentric coordinates for a given point in a triangle
		*
		* @param	Point			point to convert to barycentric coordinates (in plane of ABC)
		* @param	A,B,C			three non-collinear points defining a triangle in CCW
		* @param	Normal			Normal to triangle ABC
		* @param	InvArea			Twice area of triangle ABC
		*
		* @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
		*		  or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
		*/
		FORCEINLINE static FVector3f ComputeBaryCentric2D(const FVector3f& Point, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& Normal, const float& InvArea)
		{
			// Compute a contribution
			const float AreaPBC = Normal | ((B - Point) ^ (C - Point));
			const float a		= AreaPBC * InvArea;

			// Compute b contribution
			const float AreaPCA = Normal | ((C - Point) ^ (A - Point));
			const float b		= AreaPCA * InvArea;

			// Compute c contribution
			return FVector3f(a, b, 1.0f - a - b);
		}

	#pragma endregion Triangle

	// Box
	#pragma region
	public:

		FORCEINLINE static FBox3f Convert(const FBox3d& B) { return FBox3f(Convert(B.Min), Convert(B.Max)); }
		FORCEINLINE static FBox3d Convert(const FBox3f& B) { return FBox3d(Convert(B.Min), Convert(B.Max)); }

	#pragma endregion Box

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
		* @param OutSizeSquared		Equivalent to FVector4f::SizeSquared().
		* @param OutSize			Equivlanet to FVector4f::Size().
		* @param Tolerance			Minimum squared linear color "length".
		* @return					A normalized copy if safe, (0.0f, 0.0f, 0.0f, 0.0f) otherwise.
		*/
		FORCEINLINE static FLinearColor GetSafeNormal(const FLinearColor& Color, float& OutSizeSquared, float& OutSize, const float& Tolerance = SMALL_NUMBER)
		{
			return FLinearColor(GetSafeNormal(FVector4f(Color), OutSizeSquared, OutSize, Tolerance));
		}

	#pragma endregion LinearColor
	};
}