// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Movement.h"

// Library
#include "Library/CsLibrary_Math.h"
// Curve
#include "Curves/CurveFloat.h"

// SpeedFormat
#pragma region

namespace NCsSpeedFormat
{
	namespace Ref
	{
		typedef EMCsSpeedFormat EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UUpS, "Unreal Units per Second");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MpH, "Miles per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KpH, "Kilometers per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedFormat_MAX, "MAX");
	}
}

#pragma endregion SpeedFormat

// FCsSpeed
#pragma region

#if WITH_EDITOR

void FCsSpeed::OnPostEditChange(const FName& PropertyName)
{
	// UUpS
	if (PropertyName == FName("UUpS"))
		FromUUpS();
	// MpH
	else
	if (PropertyName == FName("MpH"))
		FromMpH();
	// KpH
	else
	if (PropertyName == FName("KpH"))
		FromKpH();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsSpeed

// FCsAcceleration
#pragma region

#if WITH_EDITOR

void FCsAcceleration::OnPostEditChange(const FName& PropertyName)
{
	// UUpSS
	if (PropertyName == FName("UUpSS"))
		FromUUpSS();
	// MpHS
	else
	if (PropertyName == FName("MpHS"))
		FromMpHS();
	// KpHS
	else
	if (PropertyName == FName("KpHS"))
		FromKpHS();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsAcceleration

// SpeedInterpMethod
#pragma region

namespace NCsSpeedInterpMethod
{
	namespace Ref
	{
		typedef EMCsSpeedInterpMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Acceleration);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Easing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Curve);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpMethod_MAX, "MAX");
	}
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

namespace NCsSpeedInterpDirection
{
	namespace Ref
	{
		typedef EMCsSpeedInterpDirection EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Increasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Decreasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpDirection_MAX, "MAX");
	}
}

#pragma endregion SpeedInterpDirection

// FCsSpeedInterp
#pragma region

bool FCsSpeedInterp::IsValidChecked() const 
{
	return true;
}

#if WITH_EDITOR

void FCsSpeedInterp::OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName)
{
	// Acceleration
	if (PropertyNames.Find(TEXT("Acceleration")))
		Acceleration.OnPostEditChange(PropertyName);
}

#endif // #if WITH_EDITOR

#pragma endregion FCsSpeedInterp

// FCsSpeedInterpHelper
#pragma region

void FCsSpeedInterpHelper::SetMinSpeed(const float& Speed)
{
	checkf(MaxSpeed > 0.0f, TEXT("FCsSpeedInterpHelper::SetMinSpeed: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

	checkf(Speed <= MaxSpeed, TEXT("FCsSpeedInterpHelper::SetMinSpeed: Speed > MaxSpeed (%f > %f)."), Speed, MaxSpeed);

	if (Speed != MinSpeed)
	{
		MinSpeed		  = Speed;
		MinSpeedAsPercent = MinSpeed / MaxSpeed;
		MinBound		  = MinSpeedAsPercent;
	}
}

void FCsSpeedInterpHelper::SetTargetSpeed(const float& Speed)
{
	checkf(MaxSpeed > 0.0f, TEXT("FCsSpeedInterpHelper::SetTargetSpeed: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

	checkf(Speed <= MaxSpeed, TEXT("FCsSpeedInterpHelper::SetTargetSpeed: Speed > MaxSpeed (%f > %f)."), Speed, MaxSpeed);

	if (Speed != TargetSpeed)
	{
		TargetSpeed			 = Speed;
		TargetSpeedAsPercent = TargetSpeed / MaxSpeed;
	}
}

void FCsSpeedInterpHelper::SetTargetSpeedAsPercent(const float& Percent)
{
	checkf(MaxSpeed > 0.0f, TEXT("FCsSpeedInterpHelper::SetTargetSpeedAsPercent: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

	checkf(Percent >= -1.0f && Percent <= 1.0f, TEXT("FCsSpeedInterpHelper::SetTargetSpeedAsPercent: Percent: %f should be between [-1.0f, 1.0f] inclusive."), Percent);

	if (Percent != TargetSpeedAsPercent)
	{
		TargetSpeedAsPercent = Percent;
		TargetSpeed			 = FMath::Abs(TargetSpeedAsPercent) * MaxSpeed;
	}
}

void FCsSpeedInterpHelper::SetInterp(FCsSpeedInterp* InInterp)
{
	checkf(InInterp, TEXT("FCsSpeedInterpHelper::SetInterp: InInterp is NULL."));

	Interp = InInterp;

	checkf(Interp->IsValidChecked(), TEXT("FCsSpeedInterpHelper::SetInterp: Interp is NOT Valid."));

	DirectionSign = Interp->Direction == ECsSpeedInterpDirection::Increasing ? 1.0f : -1.0f;

	// Acceleration
	if (Interp->Method == ECsSpeedInterpMethod::Acceleration)
	{
		checkf(MaxSpeed > 0.0f, TEXT("FCsSpeedInterpHelper::SetInterp: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

		AccelerationAsPercent = Interp->Acceleration.UUpSS / MaxSpeed;
	}
}

void FCsSpeedInterpHelper::SetCurrentSpeedAsPercent(const float& Percent)
{
	// Easing
	if (Interp->Method == ECsSpeedInterpMethod::Easing)
	{
		// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, 1.0f]
		float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (1.0f - MinSpeedAsPercent);

		// TODO: Get the Alpha that corresponds to the Percent
		CurrentAlpha = RemappedPercent;
	}
	// Curve
	else
	if (Interp->Method == ECsSpeedInterpMethod::Curve)
	{
		// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, 1.0f]
		float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (1.0f - MinSpeedAsPercent);

		// TODO: Get the Alpha that corresponds to the Percent
		// TODO: Use Curve Lookup Table
		CurrentAlpha = RemappedPercent;
	}
	CurrentSpeedAsPercent = Percent;
}

float FCsSpeedInterpHelper::GetCurrentSpeedAsPercent(const float& DeltaTime) const
{
	if (TargetSpeedAsPercent == CurrentSpeedAsPercent)
		return CurrentSpeedAsPercent;

	// Acceleration
	if (Interp->Method == ECsSpeedInterpMethod::Acceleration)
	{
		// Increasing to TargetSpeedAsPercent
		if (DirectionSign > 0)
		{
			if (bMinBound)
				return FMath::Clamp(CurrentSpeedAsPercent + DeltaTime * AccelerationAsPercent, MinBound, TargetSpeedAsPercent);
			else
				return FMath::Min(CurrentSpeedAsPercent + DeltaTime * AccelerationAsPercent, TargetSpeedAsPercent);
		}
		// Decreasing to TargetSpeedAsPercent
		else
		{
			if (bMaxBound)
				return FMath::Clamp(CurrentSpeedAsPercent - DeltaTime * AccelerationAsPercent, TargetSpeedAsPercent, MaxBound);
			else
				return FMath::Max(TargetSpeedAsPercent, CurrentSpeedAsPercent - DeltaTime * AccelerationAsPercent);
		}
	}
	// Easing
	else
	if (Interp->Method == ECsSpeedInterpMethod::Easing)
	{
		float Alpha					  = CurrentAlpha;
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		Alpha						= FMath::Clamp(Alpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent		    = FCsLibrary_Math::Ease(Interp->Easing, Alpha, 0.0f, 1.0f, 1.0f);
		const float AdjustedPercent = Interp->Direction == ECsSpeedInterpDirection::Increasing ? Percent : 1.0f - Percent;

		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

		// Increasing
		if (Interp->Direction == ECsSpeedInterpDirection::Increasing)
			return FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
		// Decreasing
		else
			return FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
	}
	// Curve
	else
	if (Interp->Method == ECsSpeedInterpMethod::Curve)
	{
		float Alpha					  = CurrentAlpha;
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		Alpha						= FMath::Clamp(Alpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent			= Interp->Curve->GetFloatValue(Alpha);
		const float AdjustedPercent = Interp->Direction == ECsSpeedInterpDirection::Increasing ? Percent : 1.0f - Percent;

		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

		// Increasing
		if (Interp->Direction == ECsSpeedInterpDirection::Increasing)
			return FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
		// Decreasing
		else
			return FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
	}
	return CurrentSpeedAsPercent;
}

void FCsSpeedInterpHelper::Update(const float& DeltaTime)
{
	if (TargetSpeedAsPercent == CurrentSpeedAsPercent)
		return;

	// Acceleration
	if (Interp->Method == ECsSpeedInterpMethod::Acceleration)
	{
		// Increasing to TargetSpeedAsPercent
		if (DirectionSign > 0)
		{
			if (bMinBound)
				CurrentSpeedAsPercent = FMath::Clamp(CurrentSpeedAsPercent + DeltaTime * AccelerationAsPercent, MinBound, TargetSpeedAsPercent);
			else
				CurrentSpeedAsPercent =  FMath::Min(CurrentSpeedAsPercent + DeltaTime * AccelerationAsPercent, TargetSpeedAsPercent);
		}
		// Decreasing to TargetSpeedAsPercent
		else
		{
			if (bMaxBound)
				CurrentSpeedAsPercent = FMath::Clamp(CurrentSpeedAsPercent - DeltaTime * AccelerationAsPercent, TargetSpeedAsPercent, MaxBound);
			else
				CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, CurrentSpeedAsPercent - DeltaTime * AccelerationAsPercent);
		}
	}
	// Easing
	else
	if (Interp->Method == ECsSpeedInterpMethod::Easing)
	{
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		CurrentAlpha				= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent		    = FCsLibrary_Math::Ease(Interp->Easing, CurrentAlpha, 0.0f, 1.0f, 1.0f);
		const float AdjustedPercent = Interp->Direction == ECsSpeedInterpDirection::Increasing ? Percent : 1.0f - Percent;

		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

		// Increasing
		if (Interp->Direction == ECsSpeedInterpDirection::Increasing)
			CurrentSpeedAsPercent = FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
		// Decreasing
		else
			CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
	}
	// Curve
	else
	if (Interp->Method == ECsSpeedInterpMethod::Curve)
	{
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		CurrentAlpha				= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent			= Interp->Curve->GetFloatValue(CurrentAlpha);
		const float AdjustedPercent = Interp->Direction == ECsSpeedInterpDirection::Increasing ? Percent : 1.0f - Percent;

		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

		// Increasing
		if (Interp->Direction == ECsSpeedInterpDirection::Increasing)
			CurrentSpeedAsPercent = FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
		// Decreasing
		else
			CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
	}
}

#pragma endregion FCsSpeedInterpHelper