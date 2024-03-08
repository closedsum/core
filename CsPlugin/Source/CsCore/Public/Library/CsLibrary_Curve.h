// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UCurveBase;
class UObject;

namespace NCsCurve
{
	/**
	* Library of functions related to Curves
	*/
	struct CSCORE_API FLibrary final
	{
	// Time
	#pragma region
	public:

	#if WITH_EDITOR
		static bool IsTimeRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinTime, const float& MaxTime);
	#else	
		FORCEINLINE static bool IsTimeRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinTime, const float& MaxTime) { return true; }
	#endif // #if WITH_EDITOR

	#pragma endregion Time

	// Value
	#pragma region
	public:

	#if WITH_EDITOR
		static bool IsValueRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinValue, const float& MaxValue);
	#else	
		FORCEINLINE static bool IsValueRangeInclusiveChecked(const FString& Context, const UCurveBase* Curve, const float& MinValue, const float& MaxValue) { return true; }
	#endif // #if WITH_EDITOR

	#pragma endregion Value
	};
}