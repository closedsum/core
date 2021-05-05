// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Math.h"
#include "CsCore.h"

namespace NCsMath
{
	// Easing
	#pragma region

	float FLibrary::Ease(const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration)
	{
		TCsEasingFunction EasingFunction = GetEasingFunction(EasingType);

		checkf(EasingFunction, TEXT("FCsLibrary_Math::Ease: Failed to get Easing Function for EasingType: %s."), EMCsEasingType::Get().ToChar(EasingType));

		return (*EasingFunction)(Time, Start, Final, Duration);
	}

	TCsEasingFunction FLibrary::GetEasingFunction(const ECsEasingType& EasingType)
	{
		if (EasingType == ECsEasingType::Linear)
			return &Linear;
		if (EasingType == ECsEasingType::BounceIn)
			return &BounceEaseIn;
		if (EasingType == ECsEasingType::BounceOut)
			return &BounceEaseOut;
		if (EasingType == ECsEasingType::BounceInOut)
			return &BounceEaseInOut;
		if (EasingType == ECsEasingType::CubicIn)
			return &CubicEaseIn;
		if (EasingType == ECsEasingType::CubicOut)
			return &CubicEaseOut;
		if (EasingType == ECsEasingType::CubicInOut)
			return &CubicEaseInOut;
		if (EasingType == ECsEasingType::ExpoIn)
			return &ExpoEaseIn;
		if (EasingType == ECsEasingType::ExpoOut)
			return &ExpoEaseOut;
		if (EasingType == ECsEasingType::ExpoInOut)
			return &ExpoEaseInOut;
		return &Linear;
	}

	#pragma endregion Easing
}