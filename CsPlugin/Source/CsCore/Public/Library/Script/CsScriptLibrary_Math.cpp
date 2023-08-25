// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Math.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsLog.h"

// Cached
#pragma region

namespace NCsScriptLibraryMath
{
	namespace NCached
	{
		namespace Str
		{
			// Easing
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, Ease);
			// Intersection
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, RayPlaneIntersection);
		}
	}
}

#pragma endregion Cached

#define MathLibrary NCsMath::FLibrary

UCsScriptLibrary_Math::UCsScriptLibrary_Math(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString UCsScriptLibrary_Math::GetFloatAsStringWithPrecision(const float& TheFloat, const uint8& Precision)
{
	return MathLibrary::GetFloatAsStringWithPrecision(TheFloat, Precision);
}

// Easing
#pragma region

float UCsScriptLibrary_Math::Ease(const FString& Context, const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration)
{
	using namespace NCsScriptLibraryMath::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Ease : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_VALID_RET_VALUE(EMCsEasingType, ECsEasingType, EasingType, 0.0f)

	return MathLibrary::Ease(EasingType, Time, Start, Final, Duration);
}

#pragma endregion Easing

// Vector
#pragma region

FVector3f UCsScriptLibrary_Math::Vector3dTo3f(const FVector& Vector)
{
	return MathLibrary::Convert(Vector);
}

FVector UCsScriptLibrary_Math::Vector3fTo3d(const FVector3f& Vector)
{
	return MathLibrary::Convert(Vector);
}

FVector UCsScriptLibrary_Math::Forward3d_OnlyYaw(const double& Yaw)
{
	return MathLibrary::GetForward3dOnlyYaw(Yaw);
}

FVector3f UCsScriptLibrary_Math::Forward3f_OnlyYaw(const float& Yaw)
{
	return MathLibrary::GetForward3fOnlyYaw(Yaw);
}

FVector UCsScriptLibrary_Math::Right3d_OnlyYaw(const double& Yaw)
{
	return MathLibrary::GetRight3dOnlyYaw(Yaw);
}

FVector3f UCsScriptLibrary_Math::Right3f_OnlyYaw(const float& Yaw)
{
	return MathLibrary::GetRight3fOnlyYaw(Yaw);
}

FVector3f UCsScriptLibrary_Math::Vector3f_Right3f_FromNormal(const FVector3f& Normal)
{
	return MathLibrary::GetRightFromNormal(Normal);
}

FVector UCsScriptLibrary_Math::Vector3d_Right3d_FromNormal(const FVector& Normal)
{
	return MathLibrary::GetRightFromNormal(Normal);
}

FVector3f UCsScriptLibrary_Math::Vector3f_Right3f(const FVector3f& Vector)
{
	return MathLibrary::GetRight(Vector);
}

FVector UCsScriptLibrary_Math::Vector3d_Right3d(const FVector& Vector)
{
	return MathLibrary::GetRight(Vector);
}

FVector3f UCsScriptLibrary_Math::Vector3f_Right3f_FromNormal2D(const FVector3f& Normal, FRotator3f& OutRotation)
{
	return MathLibrary::GetRightFromNormal2D(Normal, OutRotation);
}

FVector UCsScriptLibrary_Math::Vector3d_Right3d_FromNormal2D(const FVector& Normal, FRotator& OutRotation)
{
	return MathLibrary::GetRightFromNormal2D(Normal, OutRotation);
}

#pragma endregion Vector

// Rotation
#pragma region

FVector3f UCsScriptLibrary_Math::Rotator3d_Forward3f_OnlyYaw(const FRotator& Rotation)
{
	return MathLibrary::GetForward3fOnlyYaw(Rotation);
}

FVector UCsScriptLibrary_Math::Rotator3d_Forward3d_OnlyYaw(const FRotator& Rotation)
{
	return MathLibrary::GetForwardOnlyYaw(Rotation);
}

FVector3f UCsScriptLibrary_Math::Rotator3f_Forward3f_OnlyYaw(const FRotator3f& Rotation)
{
	return MathLibrary::GetForwardOnlyYaw(Rotation);
}

FVector UCsScriptLibrary_Math::Rotator3f_Forward3d_OnlyYaw(const FRotator3f& Rotation)
{
	return MathLibrary::GetForward3dOnlyYaw(Rotation);
}

FVector3f UCsScriptLibrary_Math::Rotator3d_Right3f_OnlyYaw(const FRotator& Rotation)
{
	return MathLibrary::GetRight3fOnlyYaw(Rotation);
}

FVector UCsScriptLibrary_Math::Rotator3d_Right3d_OnlyYaw(const FRotator& Rotation)
{
	return MathLibrary::GetRightOnlyYaw(Rotation);
}

FVector3f UCsScriptLibrary_Math::Rotator3f_Right3f_OnlyYaw(const FRotator3f& Rotation)
{
	return MathLibrary::GetRightOnlyYaw(Rotation);
}

FVector UCsScriptLibrary_Math::Rotator3f_Right3d_OnlyYaw(const FRotator3f& Rotation)
{
	return MathLibrary::GetRight3dOnlyYaw(Rotation);
}

#pragma endregion Rotation

// Matrix
#pragma region

FVector UCsScriptLibrary_Math::RotationMatrix44d_UnitAxis(const FRotator& Rotation, const TEnumAsByte<EAxis::Type>& Axis)
{
	return FRotationMatrix44d(Rotation).GetUnitAxis((EAxis::Type)Axis);
}

FVector UCsScriptLibrary_Math::RotationMatrix44d_Yaw_UnitAxis(const float& Yaw, const TEnumAsByte<EAxis::Type>& Axis)
{
	return FRotationMatrix44d(FRotator(0.0f, Yaw, 0.0f)).GetUnitAxis((EAxis::Type)Axis);
}

FVector UCsScriptLibrary_Math::RotationMatrix44d_UnitAxis_OnlyYaw(const FRotator& Rotation, const TEnumAsByte<EAxis::Type>& Axis)
{
	return FRotationMatrix44d(FRotator(0.0f, Rotation.Yaw, 0.0f)).GetUnitAxis((EAxis::Type)Axis);
}

#pragma endregion Matrix

// Ray
#pragma region
	
FCsRay UCsScriptLibrary_Math::MakeRay(const FVector3f& Origin, const FVector3f& Direction, const float& Distance)
{
	bool DirectionIsNormalized = true;

	if (!Direction.IsNormalized())
	{
		DirectionIsNormalized = false;

		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Math::MakeRay: Direction is NOT normalized."));
	}

	if (Distance <= 0.0f)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Math::MakeRay: Distance is NOT > 0.0f."));
	}
	return FCsRay(Origin, Direction, Distance > 0.0f ? Distance : FCsRay::GetDefaultDistance(), DirectionIsNormalized);
}

FCsRay UCsScriptLibrary_Math::MakeRay_OriginAndDirection(const FVector3f& Origin, const FVector3f& Direction)
{
	bool DirectionIsNormalized = true;

	if (!Direction.IsNormalized())
	{
		DirectionIsNormalized = false;

		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Math::MakeRay_OriginAndDirection: Direction is NOT normalized."));
	}
	return FCsRay(Origin, Direction, DirectionIsNormalized);
}

#pragma endregion Ray

// Plane
#pragma region

FPlane4f UCsScriptLibrary_Math::MakePlane(const FVector3f& Origin, const FVector3f& Normal)
{
	bool NormalIsNormalized = true;

	if (!Normal.IsNormalized())
	{
		NormalIsNormalized = false;

		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Math::MakeRay_OriginAndDirection: Direction is NOT normalized."));
	}
	return FPlane4f(Origin, NormalIsNormalized ? Normal : Normal.GetSafeNormal());
}

#pragma endregion Plane

// Intersection
#pragma region

bool UCsScriptLibrary_Math::RayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection)
{
	using namespace NCsScriptLibraryMath::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RayPlaneIntersection : Context;

	return MathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, OutT, OutIntersection);
}

#pragma endregion Intersection

#undef MathLibrary