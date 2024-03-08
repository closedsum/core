// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Math.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
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
			// Int
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, GreaterChecked_IntInt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, GreaterEqualChecked_IntInt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, LessChecked_IntInt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, LessEqualChecked_IntInt);
			// Float
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, GreaterChecked_FloatFloat);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, GreaterEqualChecked_FloatFloat);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, LessChecked_FloatFloat);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, LessEqualChecked_FloatFloat);
			// Easing
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, Ease);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, EasePercent);
			// Intersection
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, RayPlaneIntersection);
		}
	}
}

#pragma endregion Cached

#define USING_NS_CACHED using namespace NCsScriptLibraryMath::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryMath::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SET_LOG_WARNING void(*Log)(const FString&) = &FCsLog::Warning;
#define LogError &FCsLog::Error
#define MathLibrary NCsMath::FLibrary

UCsScriptLibrary_Math::UCsScriptLibrary_Math(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Int
#pragma region

bool UCsScriptLibrary_Math::GreaterChecked_IntInt(const FString& Context, const int32& A, const int32& B)
{
	CONDITIONAL_SET_CTXT(GreaterChecked_IntInt);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsIntGreaterThanChecked(Ctxt, A, B), MathLibrary::SafeIsIntGreaterThan(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::GreaterEqualChecked_IntInt(const FString& Context, const int32& A, const int32& B)
{
	CONDITIONAL_SET_CTXT(GreaterEqualChecked_IntInt);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsIntGreaterThanOrEqualChecked(Ctxt, A, B), MathLibrary::SafeIsIntGreaterThanOrEqual(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::LessChecked_IntInt(const FString& Context, const int32& A, const int32& B)
{
	CONDITIONAL_SET_CTXT(LessChecked_IntInt);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsIntLessThanChecked(Ctxt, A, B), MathLibrary::SafeIsIntLessThan(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::LessEqualChecked_IntInt(const FString& Context, const int32& A, const int32& B)
{
	CONDITIONAL_SET_CTXT(LessEqualChecked_IntInt);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsIntLessThanOrEqualChecked(Ctxt, A, B), MathLibrary::SafeIsIntLessThanOrEqual(Ctxt, A, B, LogError));
}

#pragma endregion Int

// Float
#pragma region

bool UCsScriptLibrary_Math::GreaterChecked_FloatFloat(const FString& Context, const float& A, const float& B)
{
	CONDITIONAL_SET_CTXT(GreaterChecked_FloatFloat);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsFloatGreaterThanChecked(Ctxt, A, B), MathLibrary::SafeIsFloatGreaterThan(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::GreaterEqualChecked_FloatFloat(const FString& Context, const float& A, const float& B)
{
	CONDITIONAL_SET_CTXT(GreaterEqualChecked_FloatFloat);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsFloatGreaterThanOrEqualChecked(Ctxt, A, B), MathLibrary::SafeIsFloatGreaterThanOrEqual(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::LessChecked_FloatFloat(const FString& Context, const float& A, const float& B)
{
	CONDITIONAL_SET_CTXT(LessChecked_FloatFloat);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsFloatLessThanChecked(Ctxt, A, B), MathLibrary::SafeIsFloatLessThan(Ctxt, A, B, LogError));
}

bool UCsScriptLibrary_Math::LessEqualChecked_FloatFloat(const FString& Context, const float& A, const float& B)
{
	CONDITIONAL_SET_CTXT(LessEqualChecked_FloatFloat);

	return CS_SCRIPT_GET_CHECKED(MathLibrary::IsFloatLessThanOrEqualChecked(Ctxt, A, B), MathLibrary::SafeIsFloatLessThanOrEqual(Ctxt, A, B, LogError));
}

FString UCsScriptLibrary_Math::GetFloatAsStringWithPrecision(const float& TheFloat, const uint8& Precision)
{
	return MathLibrary::GetFloatAsStringWithPrecision(TheFloat, Precision);
}

#pragma endregion Float

// Easing
#pragma region

float UCsScriptLibrary_Math::Ease(const FString& Context, const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration)
{
	CONDITIONAL_SET_CTXT(Ease);
	SET_LOG_WARNING

	CS_IS_ENUM_VALID_RET_VALUE(EMCsEasingType, ECsEasingType, EasingType, 0.0f)

	return MathLibrary::Ease(EasingType, Time, Start, Final, Duration);
}

float UCsScriptLibrary_Math::EasePercent(const FString& Context, const ECsEasingType& EasingType, const float& TimeAsPercent, const float& Start, const float& Final)
{
	CONDITIONAL_SET_CTXT(EasePercent);
	SET_LOG_WARNING

	CS_IS_ENUM_VALID_RET_VALUE(EMCsEasingType, ECsEasingType, EasingType, 0.0f)

	const float Percent = MathLibrary::Ease(EasingType, TimeAsPercent, 0.0f, 1.0f, 1.0f);

	return Start + Percent * (Final - Start);
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
	CONDITIONAL_SET_CTXT(RayPlaneIntersection);

	return MathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, OutT, OutIntersection);
}

#pragma endregion Intersection

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SET_LOG_WARNING
#undef LogError
#undef MathLibrary