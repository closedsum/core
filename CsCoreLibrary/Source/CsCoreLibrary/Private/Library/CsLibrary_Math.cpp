// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Math.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Kismet/KismetSystemLibrary.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsMath
{
	using LogClassType = NCsCore::NLibrary::FLog;

	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

	// Int
	#pragma region

	#if WITH_EDITOR

	bool FLibrary::IsIntGreaterThanChecked(const FString& Context, const int32& A, const int32& B)
	{
		CS_IS_INT_GREATER_THAN_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsIntGreaterThanOrEqualChecked(const FString& Context, const int32& A, const int32& B)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsIntLessThanChecked(const FString& Context, const int32& A, const int32& B)
	{
		CS_IS_INT_LESS_THAN_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsIntLessThanOrEqualChecked(const FString& Context, const int32& A, const int32& B)
	{
		CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsIntInRangeInclusiveChecked(const FString& Context, const int32& A, const int32& B, const int32& C)
	{
		CS_IS_INT_IN_RANGE_INCLUSIVE_CHECKED(A, B, C)
		return true;
	}

	#endif // #if WITH_EDITOR

	bool FLibrary::SafeIsIntGreaterThan(const FString& Context, const int32& A, const int32& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_INT_GREATER_THAN(A, B)
		return true;
	}

	bool FLibrary::SafeIsIntGreaterThanOrEqual(const FString& Context, const int32& A, const int32& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL(A, B)
		return true;
	}

	bool FLibrary::SafeIsIntLessThan(const FString& Context, const int32& A, const int32& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_INT_LESS_THAN(A, B)
		return true;
	}

	bool FLibrary::SafeIsIntLessThanOrEqual(const FString& Context, const int32& A, const int32& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_INT_LESS_THAN_OR_EQUAL(A, B)
		return true;
	}

	bool FLibrary::SafeIsIntInRangeInclusive(const FString& Context, const int32& A, const int32& B, const int32& C, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_INT_IN_RANGE_INCLUSIVE(A, B, C)
		return true;
	}

	#pragma endregion Int

	// Float
	#pragma region

	#if WITH_EDITOR

	bool FLibrary::IsFloatGreaterThanChecked(const FString& Context, const float& A, const float& B)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsFloatGreaterThanOrEqualChecked(const FString& Context, const float& A, const float& B)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsFloatLessThanChecked(const FString& Context, const float& A, const float& B)
	{
		CS_IS_FLOAT_LESS_THAN_CHECKED(A, B)
		return true;
	}

	bool FLibrary::IsFloatLessThanOrEqualChecked(const FString& Context, const float& A, const float& B)
	{
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(A, B)
		return true;
	}

	#endif // #if WITH_EDITOR

	bool FLibrary::SafeIsFloatGreaterThan(const FString& Context, const float& A, const float& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_FLOAT_GREATER_THAN(A, B)
		return true;
	}

	bool FLibrary::SafeIsFloatGreaterThanOrEqual(const FString& Context, const float& A, const float& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(A, B)
		return true;
	}

	bool FLibrary::SafeIsFloatLessThan(const FString& Context, const float& A, const float& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_FLOAT_LESS_THAN(A, B)
		return true;
	}

	bool FLibrary::SafeIsFloatLessThanOrEqual(const FString& Context, const float& A, const float& B, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(A, B)
		return true;
	}

	#pragma endregion Float

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
	// Bounce
		if (EasingType == ECsEasingType::BounceIn)
			return &Ease_BounceIn;
		if (EasingType == ECsEasingType::BounceOut)
			return &Ease_BounceOut;
		if (EasingType == ECsEasingType::BounceInOut)
			return &Ease_BounceInOut;
	// Quad
		if (EasingType == ECsEasingType::QuadIn)
			return &Ease_QuadIn;
		if (EasingType == ECsEasingType::QuadOut)
			return &Ease_QuadOut;
		if (EasingType == ECsEasingType::QuadInOut)
			return &Ease_QuadInOut;
	// Cubic
		if (EasingType == ECsEasingType::CubicIn)
			return &Ease_CubicIn;
		if (EasingType == ECsEasingType::CubicOut)
			return &Ease_CubicOut;
		if (EasingType == ECsEasingType::CubicInOut)
			return &Ease_CubicInOut;
	// Expo
		if (EasingType == ECsEasingType::ExpoIn)
			return &Ease_ExpoIn;
		if (EasingType == ECsEasingType::ExpoOut)
			return &Ease_ExpoOut;
		if (EasingType == ECsEasingType::ExpoInOut)
			return &Ease_ExpoInOut;
	// Back
		if (EasingType == ECsEasingType::BackIn)
			return &Ease_BackIn;
		if (EasingType == ECsEasingType::BackOut)
			return &Ease_BackOut;
		if (EasingType == ECsEasingType::BackInOut)
			return &Ease_BackInOut;
	// Elastic
		if (EasingType == ECsEasingType::ElasticIn)
			return &Ease_ElasticIn;
		if (EasingType == ECsEasingType::ElasticOut)
			return &Ease_ElasticOut;
		if (EasingType == ECsEasingType::ElasticInOut)
			return &Ease_ElasticInOut;
		return &Linear;
	}

	#pragma endregion Easing

	// Segment
	#pragma region

	FVector3f FLibrary::ClosestPointOnSegment(const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT)
	{
		const FVector3f Segment	  = EndPoint - StartPoint;
		const FVector3f VectToPoint = Point - StartPoint;

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

	FVector FLibrary::ClosestPointOnSegment(const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, double& OutT)
	{
		const FVector Segment	  = EndPoint - StartPoint;
		const FVector VectToPoint = Point - StartPoint;

		// See if closest point is before StartPoint
		const double Dot1 = VectToPoint | Segment;
		if (Dot1 <= 0)
		{
			OutT = 0.0f;
			return StartPoint;
		}

		// See if closest point is beyond EndPoint
		const double Dot2 = Segment | Segment;
		if (Dot2 <= Dot1)
		{
			OutT = 1.0f;
			return EndPoint;
		}

		// Closest Point is within segment
		OutT = Dot1 / Dot2;
		return StartPoint + Segment * OutT;

	}

	FVector3f FLibrary::ClosestPointOnSegmentChecked(const FString& Context, const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == Endpoint"), *Context);

		return ClosestPointOnSegment(Point, StartPoint, EndPoint, OutT);
	}

	FVector FLibrary::ClosestPointOnSegmentChecked(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, double& OutT)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == Endpoint"), *Context);

		return ClosestPointOnSegment(Point, StartPoint, EndPoint, OutT);
	}

	FVector3f FLibrary::SafeClosestPointOnSegment(const FString& Context, const FVector3f& Point, const FVector3f& StartPoint, const FVector3f& EndPoint, float& OutT, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		if (StartPoint == EndPoint)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: StartPoint == Endpoint"), *Context));
		}
		return ClosestPointOnSegment(Point, StartPoint, EndPoint, OutT);
	}

	FVector FLibrary::SafeClosestPointOnSegment(const FString& Context, const FVector& Point, const FVector& StartPoint, const FVector& EndPoint, double& OutT, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::IsValidChecked(const FString& Context, const FPlane4f& Plane)
	{
		// Check Normal is Valid
		checkf(Plane.GetNormal().IsNormalized(), TEXT("%s: Plane.GetNormal() is NOT normalized."), *Context);
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, const FPlane& Plane)
	{
		// Check Normal is Valid
		checkf(Plane.GetNormal().IsNormalized(), TEXT("%s: Plane.GetNormal() is NOT normalized."), *Context);
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, const FPlane4f& Plane, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		// Check Normal is Valid
		if (!Plane.GetNormal().IsNormalized())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Plane.GetNormal() is NOT normalized."), *Context));
			return false;
		}
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, const FPlane& Plane, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::RayPlaneIntersectionChecked(const FString& Context, const FCsRay3f& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection)
	{
		check(Ray.IsValidChecked(Context));

		check(IsValidChecked(Context, Plane));

		const FVector3f& RayDir	  = Ray.End - Ray.Origin;
		const FVector3f PlaneNormal = Plane.GetNormal();

		// Check ray is not parallel to plane
		if ((RayDir | PlaneNormal) == 0.0f)
		{
			OutT = -1.0f;
			OutIntersection = FVector3f::ZeroVector;
			return false;
		}

		const FVector3f& PlaneOrigin = Plane.GetOrigin();
		const FVector3f& LineStart   = Ray.Origin;

		OutT = (((PlaneOrigin - LineStart) | PlaneNormal) / (RayDir | PlaneNormal));

		// Check intersection is not outside line segment
		if (OutT < 0.0f || OutT > 1.0f)
		{
			OutIntersection = FVector3f::ZeroVector;
			return false;
		}

		// Calculate intersection point
		OutIntersection = LineStart + RayDir * OutT;
		return true;
	}

	bool FLibrary::RayPlaneIntersectionChecked(const FString& Context, const FCsRay& Ray, const FPlane& Plane, double& OutT, FVector& OutIntersection)
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

	bool FLibrary::SafeRayPlaneIntersection(const FString& Context, const FCsRay3f& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		if (!Ray.IsValid(Context, Log))
			return false;

		if (!IsValid(Context, Plane))
			return false;

		return RayPlaneIntersectionChecked(Context, Ray, Plane, OutT, OutIntersection);
	}

	bool FLibrary::SafeRayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane& Plane, double& OutT, FVector& OutIntersection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		if (!Ray.IsValid(Context, Log))
			return false;

		if (!IsValid(Context, Plane))
			return false;

		return RayPlaneIntersectionChecked(Context, Ray, Plane, OutT, OutIntersection);
	}

	bool FLibrary::SegmentPlaneIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint)
	{
		OutT = GetTForSegmentPlaneIntersect(StartPoint, EndPoint, Plane);
		// If the parameter value is not between 0 and 1, there is no intersection
		if (OutT > -KINDA_SMALL_NUMBER && OutT < 1.f + KINDA_SMALL_NUMBER)
		{
			OutIntersectionPoint = StartPoint + OutT * (EndPoint - StartPoint);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentPlaneIntersection(const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, double& OutT, FVector& OutIntersectionPoint)
	{
		OutT = GetTForSegmentPlaneIntersect(StartPoint, EndPoint, Plane);
		// If the parameter value is not between 0 and 1, there is no intersection
		if (OutT > -KINDA_SMALL_NUMBER && OutT < 1.f + KINDA_SMALL_NUMBER)
		{
			OutIntersectionPoint = StartPoint + OutT * (EndPoint - StartPoint);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentPlaneIntersectionChecked(const FString& Context, const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == EndPoint."), *Context);
		check(IsValidChecked(Context, Plane));

		return SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectionPoint);
	}

	bool FLibrary::SegmentPlaneIntersectionChecked(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, double& OutT, FVector& OutIntersectionPoint)
	{
		checkf(StartPoint != EndPoint, TEXT("%s: StartPoint == EndPoint."), *Context);
		check(IsValidChecked(Context, Plane));

		return SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectionPoint);
	}

	bool FLibrary::SafeSegmentPlaneIntersection(const FString& Context, const FVector3f& StartPoint, const FVector3f& EndPoint, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersectionPoint, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SafeSegmentPlaneIntersection(const FString& Context, const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, double& OutT, FVector& OutIntersectionPoint, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

	bool FLibrary::SegmentQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, float& OutT, FVector3f& OutIntersectPoint, FVector3f& OutNormal)
	{
		FVector3f Edge1(B - A);
		Edge1.Normalize();
		FVector3f Edge2(C - A);
		Edge2.Normalize();
		FVector3f TriNormal = Edge2 ^ Edge1;
		TriNormal.Normalize();

		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, FPlane4f(A, TriNormal), OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector3f BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, double& OutT, FVector& OutIntersectPoint, FVector& OutNormal)
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
		FVector BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentRectangleQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, float& OutT, FVector3f& OutIntersectPoint, FVector3f& OutNormal, FVector2f& OutUV)
	{
		FVector3f Edge1(B - A);
		Edge1.Normalize();
		FVector3f Edge2(C - A);
		Edge2.Normalize();
		FVector3f TriNormal = Edge2 ^ Edge1;
		TriNormal.Normalize();

		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, FPlane4f(A, TriNormal), OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector3f BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentRectangleQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, double& OutT, FVector& OutIntersectPoint, FVector& OutNormal, FVector2D& OutUV)
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
		FVector BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			OutNormal = TriNormal;

			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentRectangleQuadIntersection(const FVector3f& StartPoint, const FVector3f& EndPoint, const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& D, const FPlane4f& Plane, const FVector3f& ABC_Normal, const float& ABC_InvArea, const FVector3f& ADC_Normal, const float& ADC_InvArea, float& OutT, FVector3f& OutIntersectPoint, FVector2f& OutUV)
	{
		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector3f BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C, ABC_Normal, ABC_InvArea);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C, ADC_Normal, ADC_InvArea);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}
		return false;
	}

	bool FLibrary::SegmentRectangleQuadIntersection(const FVector& StartPoint, const FVector& EndPoint, const FVector& A, const FVector& B, const FVector& C, const FVector& D, const FPlane& Plane, const FVector& ABC_Normal, const double& ABC_InvArea, const FVector& ADC_Normal, const double& ADC_InvArea, double& OutT, FVector& OutIntersectPoint, FVector2D& OutUV)
	{
		bool Collide = SegmentPlaneIntersection(StartPoint, EndPoint, Plane, OutT, OutIntersectPoint);
		if (!Collide)
		{
			return false;
		}

		// Check Triangle ABC
		FVector BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, B, C, ABC_Normal, ABC_InvArea);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}

		// Check Triangle ADC
		BaryCentric = ComputeBaryCentric2D(OutIntersectPoint, A, D, C, ADC_Normal, ADC_InvArea);
		if (BaryCentric.X > 0.0f && BaryCentric.Y > 0.0f && BaryCentric.Z > 0.0f)
		{
			ClosestPointOnSegment(OutIntersectPoint, A, B, OutUV.X);
			ClosestPointOnSegment(OutIntersectPoint, A, D, OutUV.Y);
			return true;
		}
		return false;
	}

	#pragma endregion Intersection
}