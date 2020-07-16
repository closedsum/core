// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Math.h"
#include "CsCore.h"

float FCsLibrary_Math::BytesToKilobytes(const int32& Bytes)
{
	return Bytes * FMath::Pow(10, -3);
}

float FCsLibrary_Math::BytesToMegabytes(const int32& Bytes)
{
	return Bytes * FMath::Pow(10, -6);
}

int32 FCsLibrary_Math::KilobytesToBytes(const float& Kilobytes)
{
	return Kilobytes * FMath::Pow(10, 3);
}

// Easing
#pragma region

float FCsLibrary_Math::Ease(const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration)
{
	TCsEasingFunction EasingFunction = GetEasingFunction(EasingType);

	checkf(EasingFunction, TEXT("FCsLibrary_Math::Ease: Failed to get Easing Function for EasingType: %s."), EMCsEasingType::Get().ToChar(EasingType));

	return (*EasingFunction)(Time, Start, Final, Duration);
}

float FCsLibrary_Math::Linear(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	return ((Final * Time) / Duration) + Start;
}

float FCsLibrary_Math::BounceEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

float FCsLibrary_Math::BounceEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	return Final - BounceEaseOut(Duration - Time, 0, Final, Duration) + Start;
}

float FCsLibrary_Math::BounceEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	if (Time < (Duration / 2.0f))
		return (BounceEaseIn(Time * 2, 0, Final, Duration) * 0.5f) + Start;
	else
		return (BounceEaseOut(Time * 2 - Duration, 0, Final, Duration) * 0.5f) + Final * 0.5f + Start;
}

float FCsLibrary_Math::CubicEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	float T = Time;
	T /= Duration;
	return Final * T * T * T + Start;
}

float FCsLibrary_Math::CubicEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	float T = Time;
	T = (T / Duration) - 1.0f;
	return Final * ((T *  T * T) + 1) + Start;
}

float FCsLibrary_Math::CubicEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

float FCsLibrary_Math::ExpoEaseIn(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	return (Time == 0.0f) ? Start : Final * FMath::Pow(2.0f, 10.0f * (Time / Duration - 1.0f)) + Start;
}

float FCsLibrary_Math::ExpoEaseOut(const float& Time, const float& Start, const float& Final, const float& Duration)
{
	return (Time == Duration) ? Start + Final : Final * (-1.0f * FMath::Pow(2.0f, -10.0f * Time / Duration) + 1.0f) + Start;
}

float FCsLibrary_Math::ExpoEaseInOut(const float& Time, const float& Start, const float& Final, const float& Duration)
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

TCsEasingFunction FCsLibrary_Math::GetEasingFunction(const ECsEasingType& EasingType)
{
	if (EasingType == ECsEasingType::Linear)
		return &FCsLibrary_Math::Linear;
	if (EasingType == ECsEasingType::BounceIn)
		return &FCsLibrary_Math::BounceEaseIn;
	if (EasingType == ECsEasingType::BounceOut)
		return &FCsLibrary_Math::BounceEaseOut;
	if (EasingType == ECsEasingType::BounceInOut)
		return &FCsLibrary_Math::BounceEaseInOut;
	if (EasingType == ECsEasingType::CubicIn)
		return &FCsLibrary_Math::CubicEaseIn;
	if (EasingType == ECsEasingType::CubicOut)
		return &FCsLibrary_Math::CubicEaseOut;
	if (EasingType == ECsEasingType::CubicInOut)
		return &FCsLibrary_Math::CubicEaseInOut;
	if (EasingType == ECsEasingType::ExpoIn)
		return &FCsLibrary_Math::ExpoEaseIn;
	if (EasingType == ECsEasingType::ExpoOut)
		return &FCsLibrary_Math::ExpoEaseOut;
	if (EasingType == ECsEasingType::ExpoInOut)
		return &FCsLibrary_Math::ExpoEaseInOut;
	return &FCsLibrary_Math::Linear;
}

#pragma endregion Easing