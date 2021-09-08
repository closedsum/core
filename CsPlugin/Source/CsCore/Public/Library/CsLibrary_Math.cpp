// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Math.h"
#include "CsCore.h"

// Library
#include "Kismet/KismetSystemLibrary.h"

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

	// Plane
	#pragma region

	bool FLibrary::IsValidChecked(const FString& Context, const FPlane& Plane)
	{
		// Check Normal is Valid
		checkf(Plane.GetNormal().IsNormalized(), TEXT("%s: Plane.GetNormal() is NOT normalized."), *Context);
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, const FPlane& Plane, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Normal is Valid
		if (!Plane.GetNormal().IsNormalized())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Plane.GetNormal() is NOT normalized."), *Context));
			return false;
		}
		return true;
	}

	#pragma endregion Plane

	// Intersection
	#pragma region

	bool FLibrary::RayPlaneIntersectionChecked(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection)
	{
		check(Ray.IsValidChecked(Context));

		check(IsValidChecked(Context, Plane));

		const FVector& RayDir	  = Ray.End - Ray.Origin;
		const FVector PlaneNormal = Plane.GetNormal();

		// Check ray is not parallel to plane
		if ((RayDir | PlaneNormal) == 0.0f)
		{
			OutT = -1.0f;
			OutIntersection = FVector::ZeroVector;
			return false;
		}

		const FVector& PlaneOrigin = Plane.GetOrigin();
		const FVector& LineStart   = Ray.Origin;

		OutT = (((PlaneOrigin - LineStart) | PlaneNormal) / (RayDir | PlaneNormal));

		// Check intersection is not outside line segment
		if (OutT < 0.0f || OutT > 1.0f)
		{
			OutIntersection = FVector::ZeroVector;
			return false;
		}

		// Calculate intersection point
		OutIntersection = LineStart + RayDir * OutT;
		return true;
	}

	bool FLibrary::SafeRayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (!Ray.IsValid(Context, Log))
			return false;

		if (!IsValid(Context, Plane))
			return false;

		return RayPlaneIntersectionChecked(Context, Ray, Plane, OutT, OutIntersection);
	}

	#pragma endregion Intersection
}