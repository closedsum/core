// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Interpolation.h"

/**
*/
class CSCORE_API FCsLibrary_Math
{
public:

	static float BytesToKilobytes(const int32& Bytes);

	static float BytesToMegabytes(const int32& Bytes);

	static int32 KilobytesToBytes(const float& Kilobytes);

// Easing
#pragma region
public:

	static float Ease(const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration);
	
	static float Linear(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float BounceEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float BounceEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float BounceEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float CubicEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float CubicEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float CubicEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float ExpoEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float ExpoEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration);
	static float ExpoEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration);

	static TCsEasingFunction GetEasingFunction(const ECsEasingType& EasingType);

#pragma endregion Easing
};