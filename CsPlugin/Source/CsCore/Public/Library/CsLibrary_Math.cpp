// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Math.h"
#include "CsCore.h"
// Easing
#pragma region

float FCsLibrary_Math::Ease(const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration)
{
	TCsEasingFunction EasingFunction = GetEasingFunction(EasingType);

	checkf(EasingFunction, TEXT("FCsLibrary_Math::Ease: Failed to get Easing Function for EasingType: %s."), EMCsEasingType::Get().ToChar(EasingType));

	return (*EasingFunction)(Time, Start, Final, Duration);
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