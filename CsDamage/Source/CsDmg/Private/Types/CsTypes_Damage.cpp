// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Damage.h"

// Curve
#include "Curves/CurveFloat.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Damage)

// DamageType
#pragma region

namespace NCsDamageType
{
	CSDMG_API CS_CREATE_ENUM_STRUCT(Default);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDamageType::Get().ClearUserDefinedEnums();
	}
}

#pragma endregion DamageType

// HitDirection
#pragma region

namespace NCsHitDirection
{
	namespace Ref
	{
		CSDMG_API const Type Front = EMCsHitDirection::Get().Add(Type::Front, TEXT("Front"));
		CSDMG_API const Type FrontRight = EMCsHitDirection::Get().Add(Type::FrontRight, TEXT("FrontRight"), TEXT("Front Right"));
		CSDMG_API const Type Right = EMCsHitDirection::Get().Add(Type::Right, TEXT("Right"));
		CSDMG_API const Type BackRight = EMCsHitDirection::Get().Add(Type::BackRight, TEXT("BackRight"), TEXT("Back Right"));
		CSDMG_API const Type Back = EMCsHitDirection::Get().Add(Type::Back, TEXT("Back"));
		CSDMG_API const Type BackLeft = EMCsHitDirection::Get().Add(Type::BackLeft, TEXT("BackLeft"), TEXT("Back Left"));
		CSDMG_API const Type Left = EMCsHitDirection::Get().Add(Type::Left, TEXT("Left"));
		CSDMG_API const Type FrontLeft = EMCsHitDirection::Get().Add(Type::FrontLeft, TEXT("FrontLeft"), TEXT("Front Left"));
		CSDMG_API const Type ECsHitDirection_MAX = EMCsHitDirection::Get().Add(Type::ECsHitDirection_MAX, TEXT("ECsHitDirection_MAX"), TEXT("MAX"));
	}
}

#pragma endregion HitDirection

// FCsDamageFalloff
#pragma region

float FCsDamageFalloff::GetFalloff(const float &Distance)
{
	if (MaxDistance > 0.0f && Distance > MaxDistance)
		return Minimum;

	// Easing
	if (bEasingType)
	{
		const float Percent = Distance / MaxDistance;

		return FMath::Max(Minimum, (*EasingFunction)(Percent, 0.0f, 1.0f, 1.0f));
	}
	// Curve
	else
	if (bCurve)
	{
		const float Percent = Distance / MaxDistance;

		return FMath::Max(Minimum, Curve.Get()->GetFloatValue(Percent));
	}
	// Default
	else
	{
		if (Rate == 0.0f || Frequency == 0.0f)
			return 1.0f;

		return FMath::Max(Minimum, 1.0f - (Rate * FMath::FloorToFloat(Distance / Frequency)));
	}
}

#pragma endregion FCsDamageFalloff

// FCsDamageRadial
#pragma region

float FCsDamageRadial::GetDamage(const FVector3f& Origin, const FVector3f& Location)
{
	if (DeltaRadius == 0.0f)
		return 0.0f;

	const float Distance = (Location - Origin).Size();

	if (Distance < MinRadius)
		return 0.0f;
	if (Distance > MaxRadius)
		return 0.0f;
	if (Delta == 0.0f)
		return Min;

	const float Percent = (Distance - MinRadius) / DeltaRadius;

	if (bCurve)
		return Curve.Get()->GetFloatValue(Percent) * Delta + Min;
	return (*EasingFunction)(Percent, 0.0f, 1.0f, 1.0f) * Delta + Min;
}

#pragma endregion FCsDamageRadial