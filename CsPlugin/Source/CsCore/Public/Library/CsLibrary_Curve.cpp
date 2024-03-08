// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Curve.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Curve
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "Curves/CurveLinearColor.h"

namespace NCsCurve
{
	// Time
	#pragma region

	#if WITH_EDITOR

	bool FLibrary::IsTimeRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinTime, const float& MaxTime)
	{
		CS_IS_PENDING_KILL_CHECKED(Curve)

		// Float
		if (const UCurveFloat* CurveFloat = Cast<UCurveFloat>(Curve))
		{
			float Min = 0.0f;
			float Max = 0.0f;
			CurveFloat->GetTimeRange(Min, Max);

			CS_IS_FLOAT_EQUAL_CHECKED(MinTime, Min)
			CS_IS_FLOAT_EQUAL_CHECKED(MaxTime, Max)
		}
		// Vector
		else
		if (const UCurveVector* CurveVector = Cast<UCurveVector>(Curve))
		{
			//CurveVector->GetValueRange()
		}
		return true;
	}

	#pragma endregion Time

	// Value
	#pragma region

	bool FLibrary::IsValueRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinValue, const float& MaxValue)
	{
		CS_IS_PENDING_KILL_CHECKED(Curve)

		// Float
		if (const UCurveFloat* CurveFloat = Cast<UCurveFloat>(Curve))
		{
			float Min = 0.0f;
			float Max = 0.0f;
			CurveFloat->GetValueRange(Min, Max);

			CS_IS_FLOAT_EQUAL_CHECKED(MinValue, Min)
			CS_IS_FLOAT_EQUAL_CHECKED(MaxValue, Max)
		}
		return true;
	}

	#endif // #if WITH_EDITOR

	#pragma endregion Value
}