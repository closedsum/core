// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

	// Segment
	#pragma region

	FVector FLibrary::ClosestPointOnSegment(const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT)
	{
		const FVector Segment	  = EndPoint - StartPoint;
		const FVector VectToPoint = Point - StartPoint;

		// See if closest point is before StartPoint
		const float Dot1 = VectToPoint | Segment;
		if (Dot1 <= 0)
		{
			OutT = 0.0f;
			return StartPoint;
		}

		// See if closest point is beyond EndPoint
		const float Dot2 = Segment | Segment;
		if (Dot2 <= Dot1)
		{
			OutT = 1.0f;
			return EndPoint;
		}

		// Closest Point is within segment
		OutT = Dot1 / Dot2;
		return StartPoint + Segment * OutT;
	}

	FVector FLibrary::ClosestPointOnSegmentChecked(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == Endpoint"), *Context);

		return ClosestPointOnSegment(Point, StartPoint, EndPoint, OutT);
	}

	FVector FLibrary::SafeClosestPointOnSegment(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, float& OutT, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (StartPoint == EndPoint)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: StartPoint == Endpoint"), *Context));
		}
		return ClosestPointOnSegment(Point, StartPoint, EndPoint, OutT);
	}

	#pragma endregion Segment

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

	bool FLibrary::SegmentPlaneIntersection(const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint)
	{
		OutT = FMath::GetTForSegmentPlaneIntersect(StartPoint, EndPoint, Plane);
		// If the parameter value is not between 0 and 1, there is no intersection
		if (OutT > -KINDA_SMALL_NUMBER && OutT < 1.f + KINDA_SMALL_NUMBER)
		{
			OutIntersectionPoint = StartPoint + OutT * (EndPoint - StartPoint);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentPlaneIntersectionChecked(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == EndPoint."), *Context);

		check(IsValidChecked(Context, Plane));

		return SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectionPoint);
	}

	bool FLibrary::SafeSegmentPlaneIntersection(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, float& OutT, FVector& OutIntersectionPoint, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (StartPoint == EndPoint)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: StartPoint == EndPoint."), *Context));
			return false;
		}

		if (!IsValid(Context, Plane, Log))
			return false;

		return SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectionPoint);
	}

	bool FLibrary::SegmentQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, float& OutT, FVector& OutIntersectPoint, FVector& OutNormal)
	{
		FVector Edge1(B - A);
		Edge1.Normalize();
		FVector Edge2(C - A);
		Edge2.Normalize();
		FVector TriNormal = Edge2 ^ Edge1;
		TriNormal.Normalize();

		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, FPlane(A, TriNormal), OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector BaryCentric = FMath::ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}

		// Check Triangle ADC
		BaryCentric = FMath::ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentRectangleQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, float& OutT, FVector& OutIntersectPoint, FVector& OutNormal, FVector2D& OutUV)
	{
		FVector Edge1(B - A);
		Edge1.Normalize();
		FVector Edge2(C - A);
		Edge2.Normalize();
		FVector TriNormal = Edge2 ^ Edge1;
		TriNormal.Normalize();

		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, FPlane(A, TriNormal), OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector BaryCentric = FMath::ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}

		// Check Triangle ADC
		BaryCentric = FMath::ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}
		return false;
	}

	#pragma endregion Intersection
}