// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

		FORCEINLINE static FRotator GetAngleDelta(const FRotator& A, const FRotator& B)
		{
			FRotator Rotation;

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

		FORCEINLINE static FRotator GetAbsAngleDelta(const FRotator& A, const FRotator& B)
		{
			FRotator Rotation;

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

		FORCEINLINE static FRotator AngleClamp180(const FRotator& Rotation)
		{
			return FRotator(AngleClamp180(Rotation.Pitch), AngleClamp180(Rotation.Yaw), AngleClamp180(Rotation.Roll));
		}

		FORCEINLINE static float AngleClamp360(float Angle)
		{
			while (Angle < 0.0f) { Angle += 360.0f; }
			while (Angle > 360.0f) { Angle -= 360.0f; }
			return Angle;
		}

		FORCEINLINE static FRotator AngleClamp360(const FRotator& Rotation)
		{
			return FRotator(AngleClamp360(Rotation.Pitch), AngleClamp360(Rotation.Yaw), AngleClamp360(Rotation.Roll));
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

			return (1.0f / OutSize) * FVector(V.X, V.Y, 0.f);
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

		/**
		* Call V.Rotation() and return the rotation with ONLY the Yaw value as
		* Yaw + Offset.
		* 
		* @param V
		* @param Offset		Value to be added to V.Rotation().Yaw.
		* return			FRotator(0.0f, V.Rotation().Yaw + Offset, 0.0f).
		*/
		FORCEINLINE static FRotator ToRotatorOnlyYaw(const FVector& V, const float& Offset = 0.0f)
		{
			FRotator R = FRotator::ZeroRotator;

			R.Yaw = FMath::Atan2(V.Y, V.X) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (R.ContainsNaN())
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::ToRotatorOnlyYaw(): Rotator result %s contains NaN! Input FVector = %s"), *(R.ToString()), *(V.ToString()));
				R = FRotator::ZeroRotator;
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
		FORCEINLINE static float GetYaw(const FVector& V)
		{
			const float Yaw = FMath::Atan2(V.Y, V.X) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (!FMath::IsFinite(Yaw))
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::GetYaw(): Yaw result %f contains NaN! Input FVector = %s"), Yaw, *(V.ToString()));
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
		* return			FRotator(0.0f, V.Rotation().Pitch + Offset, 0.0f).
		*/
		FORCEINLINE static FRotator ToRotatorOnlyPitch(const FVector& V, const float& Offset = 0.0f)
		{
			FRotator R = FRotator::ZeroRotator;

			R.Pitch = FMath::Atan2(V.Z, FMath::Sqrt((V.X * V.X) + (V.Y * V.Y))) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (R.ContainsNaN())
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::ToRotatorOnlyYaw(): Rotator result %s contains NaN! Input FVector = %s"), *(R.ToString()), *(V.ToString()));
				R = FRotator::ZeroRotator;
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
		FORCEINLINE static float GetPitch(const FVector& V)
		{
			const float Pitch = FMath::Atan2(V.Z, FMath::Sqrt((V.X * V.X) + (V.Y * V.Y))) * (180.f / PI);

#if ENABLE_NAN_DIAGNOSTIC || (DO_CHECK && !UE_BUILD_SHIPPING)
			if (!FMath::IsFinite(Pitch))
			{
				logOrEnsureNanError(TEXT("NCsMath::FLibrary::GetPitch(): Pitch result %f contains NaN! Input FVector = %s"), Pitch, *(V.ToString()));
				return 0.0f;
			}
#endif
			return Pitch;
		}

		FORCEINLINE static bool IsAnyComponentZero(const FVector& V)
		{
			return V.X == 0.0f || V.Y == 0.0f || V.Z == 0.0f;
		}

		FORCEINLINE static FVector Limit2D(const FVector& V, const float& Max)
		{
			if (Max == 0.0f)
				return FVector::ZeroVector;

			const float DSq = V.SizeSquared2D();
			
			if (DSq > (Max * Max))
			{
				return (Max / DSq) * V;
			}
			return V;
		}

		FORCEINLINE static FVector GetUpFromNormal(const FVector& N) { return GetUp(N.Rotation()); }
		FORCEINLINE static FVector GetUp(const FVector& V) { return GetUpFromNormal(V.GetSafeNormal()); }

		FORCEINLINE static FVector GetRightFromNormal(const FVector& N) { return GetRight(N.Rotation()); }
		FORCEINLINE static FVector GetRight(const FVector& V) { return GetRightFromNormal(V.GetSafeNormal()); }
		FORCEINLINE static FVector GetRightFromNormal2D(const FVector& N) { return GetRightOnlyYaw(GetYaw(N)); }

		FORCEINLINE static void GetRightAndUpFromNormal(const FVector& N, FVector& OutRight, FVector& OutUp) { GetRightAndUp(N.Rotation(), OutRight, OutUp); }

		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of the 'Up' vector relative to N.
		* 
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Up' vector relative to N.
		*/
		FORCEINLINE static FVector RotateNormalAngleUp(const FVector& N, const float& Angle) { return N.RotateAngleAxis(Angle, GetUpFromNormal(N)); }
		
		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of World Up (FVector::UpVector).
		*
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Up' vector relative to N.
		*/
		FORCEINLINE static FVector RotateNormalWorldUp(const FVector& N, const float& Angle) { return N.RotateAngleAxis(Angle, FVector::UpVector); }

		/**
		* Rotate a Normalized Vector, N, by Angle Degrees about the Axis made of the 'Right' vector relative to N.
		*
		* @param N		Normalized Vector
		* @param Angle	Angle in Degrees
		* return		N rotated Angle Degrees about 'Right' vector relative to N.
		*/
		FORCEINLINE static FVector RotateNormalAngleRight(const FVector& N, const float& Angle) { return N.RotateAngleAxis(Angle, GetRightFromNormal(N));  }

		FORCEINLINE static FVector Fractional(const FVector& V)
		{
			return FVector(FMath::Fractional(V.X), FMath::Fractional(V.Y), FMath::Fractional(V.Z));
		}

		FORCEINLINE static float DotProduct2D(const FVector& A, const FVector& B)
		{
			return A.X * B.X + A.Y * B.Y;
		}

	#pragma endregion Vector

	// Rotator
	#pragma region
	public:

		FORCEINLINE static FVector GetRight(const FRotator& R) { return FRotationMatrix(R).GetScaledAxis(EAxis::Y); }
		FORCEINLINE static FVector GetRightOnlyYaw(const float& Yaw)
		{
			float SY, CY;
			FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Yaw));

			return FVector(-SY, CY, 0.0f);
		}
		FORCEINLINE static FVector GetRightOnlyYaw(const FRotator& R)
		{
			return GetRightOnlyYaw(R.Yaw);
		}

		FORCEINLINE static FVector GetUp(const FRotator& R) { return FRotationMatrix(R).GetScaledAxis(EAxis::Z); }

		FORCEINLINE static void GetForwardRightAndUp(const FRotator& R, FVector& OutForward, FVector& OutRight, FVector& OutUp)
		{
			FRotationMatrix M(R);
			OutForward = M.GetScaledAxis(EAxis::X);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

		FORCEINLINE static void GetRightAndUp(const FRotator& R, FVector& OutRight, FVector& OutUp)
		{
			FRotationMatrix M(R);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

	#pragma endregion Rotator

	// Quat
	#pragma region
	public:

		FORCEINLINE static FVector GetRight(const FQuat& Q) { return GetRight(Q.Rotator()); }
		FORCEINLINE static FVector GetUp(const FQuat& Q) { return GetUp(Q.Rotator()); }

		FORCEINLINE static void GetForwardRightAndUp(const FQuat& Q, FVector& OutForward, FVector& OutRight, FVector& OutUp)
		{
			FMatrix M = FRotationMatrix::Make(Q);
			OutForward = M.GetScaledAxis(EAxis::X);
			OutRight = M.GetScaledAxis(EAxis::Y);
			OutUp = M.GetScaledAxis(EAxis::Z);
		}

	#pragma endregion Quat

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
		static FVector ClosestPointOnSegment(const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT);

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
		static FVector ClosestPointOnSegmentChecked(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT);

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
		static FVector SafeClosestPointOnSegment(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Segment

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
		static bool SegmentPlaneIntersection(const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint);

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
		static bool SegmentPlaneIntersectionChecked(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint);

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
		static bool SafeSegmentPlaneIntersection(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static bool SegmentQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, float& OutT, FVector& OutIntersectPoint, FVector& OutNormal);

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
		static bool SegmentRectangleQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, float& OutT, FVector& OutIntersectPoint, FVector& OutNormal, FVector2D& OutUV);

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
		static bool SegmentRectangleQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, const FPlane& Plane, const FVector& ABC_Normal, const float& ABC_InvArea, const FVector& ADC_Normal, const float& ADC_InvArea, float& OutT, FVector& OutIntersectPoint, FVector2D& OutUV);

	#pragma endregion Intersection

	// Triangle
	#pragma region
	public:

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
		FORCEINLINE static FVector ComputeBaryCentric2D(const FVector& Point, const FVector& A, const FVector& B, const FVector& C, const FVector& Normal, const float& InvArea)
		{
			// Compute a contribution
			const float AreaPBC = Normal | ((B - Point) ^ (C - Point));
			const float a		= AreaPBC * InvArea;

			// Compute b contribution
			const float AreaPCA = Normal | ((C - Point) ^ (A - Point));
			const float b		= AreaPCA * InvArea;

			// Compute c contribution
			return FVector(a, b, 1.0f - a - b);
		}

	#pragma endregion Triangle

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