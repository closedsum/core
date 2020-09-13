// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Movement.h"

// Library
#include "Library/CsLibrary_Math.h"
// Curve
#include "Curves/CurveFloat.h"

// SpeedInterpMethod
#pragma region

namespace NCsSpeedInterpMethod
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpeedInterpMethod, Acceleration);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpeedInterpMethod, Easing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpeedInterpMethod, Curve);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpeedInterpMethod, ECsSpeedInterpMethod_MAX, "MAX");
	}
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

namespace NCsSpeedInterpDirection
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpeedInterpDirection, Increasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpeedInterpDirection, Decreasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpeedInterpDirection, ECsSpeedInterpDirection_MAX, "MAX");
	}
}

#pragma endregion SpeedInterpDirection

// FCsSpeedInterp
#pragma region

bool FCsSpeedInterp::IsValidChecked() const 
{
	return true;
}

#pragma endregion FCsSpeedInterp

// FCsSpeedInterpHelper
#pragma region

void FCsSpeedInterpHelper::SetMinSpeed(const float& Speed)
{
	checkf(MaxSpeed <= 0.0f, TEXT("FCsSpeedInterpHelper::SetMinSpeed: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

	checkf(Speed <= MaxSpeed, TEXT("FCsSpeedInterpHelper::SetMinSpeed: Speed > MaxSpeed (%f > %f)."), Speed, MaxSpeed);

	MinSpeed		  = Speed;
	MinSpeedAsPercent = MinSpeed / MaxSpeed;
}

void FCsSpeedInterpHelper::SetTargetSpeed(const float& Speed)
{
	TargetSpeed			 = Speed;
	TargetSpeedAsPercent = TargetSpeed / MaxSpeed;
}

void FCsSpeedInterpHelper::SetInterp(FCsSpeedInterp* InInterp)
{
	checkf(InInterp, TEXT("FCsSpeedInterpHelper::SetInterp: InInterp is NULL."));

	Interp = InInterp;

	checkf(Interp->IsValidChecked(), TEXT(""));

	// Acceleration
	if (Interp->Method == ECsSpeedInterpMethod::Acceleration)
	{
		checkf(MaxSpeed <= 0.0f, TEXT("FCsSpeedInterpHelper::SetInterp: MaxSpeed (%f) <= 0.0f"), MaxSpeed);

		AccelerationAsPercent = Interp->Acceleration.UUpSS / MaxSpeed;
	}
}

void FCsSpeedInterpHelper::SetCurrentSpeedAsPercent(const float& Percent)
{
	// Easing
	if (Interp->Method == ECsSpeedInterpMethod::Easing)
	{
		// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, TargetSpeedAsPercent]
		float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (TargetSpeedAsPercent - MinSpeedAsPercent);

		// TODO: Get the Alpha that corresponds to the Percent
		CurrentAlpha = RemappedPercent;
	}
	// Curve
	else
	if (Interp->Method == ECsSpeedInterpMethod::Curve)
	{
		// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, TargetSpeedAsPercent]
		float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (TargetSpeedAsPercent - MinSpeedAsPercent);

		// TODO: Get the Alpha that corresponds to the Percent
		// TODO: Use Curve Lookup Table
		CurrentAlpha = RemappedPercent;
	}
	CurrentSpeedAsPercent = Percent;
}


void FCsSpeedInterpHelper::Update(const float& DeltaTime)
{
	if (TargetSpeedAsPercent == CurrentSpeedAsPercent)
		return;

	// Acceleration
	if (Interp->Method == ECsSpeedInterpMethod::Acceleration)
	{
		CurrentSpeedAsPercent = FMath::Clamp(CurrentSpeedAsPercent + DeltaTime * AccelerationAsPercent, MinSpeedAsPercent, TargetSpeedAsPercent);
	}
	// Easing
	else
	if (Interp->Method == ECsSpeedInterpMethod::Easing)
	{
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		CurrentAlpha		= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent = FCsLibrary_Math::Ease(Interp->Easing, CurrentAlpha, 0.0f, 1.0f, 1.0f);
		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, TargetSpeedAsPercent]
		CurrentSpeedAsPercent = Percent * (TargetSpeedAsPercent - MinSpeedAsPercent) + MinSpeedAsPercent;
	}
	// Curve
	else
	if (Interp->Method == ECsSpeedInterpMethod::Curve)
	{
		const float AdjustedDeltaTime = DeltaTime / Interp->Time;

		CurrentAlpha		= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
		const float Percent = Interp->Curve->GetFloatValue(CurrentAlpha);
		// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, TargetSpeedAsPercent]
		CurrentSpeedAsPercent = Percent * (TargetSpeedAsPercent - MinSpeedAsPercent) + MinSpeedAsPercent;
	}
}

#pragma endregion FCsSpeedInterpHelper