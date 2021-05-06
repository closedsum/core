// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Math.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Math.h"

// Cached
#pragma region

namespace NCsScriptLibraryMath
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Math, RayPlaneIntersection);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Math::UCsScriptLibrary_Math(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Ray
#pragma region
	
FCsRay UCsScriptLibrary_Math::MakeRay(const FVector& Origin, const FVector& Direction, const float& Distance)
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

FCsRay UCsScriptLibrary_Math::MakeRay_OriginAndDirection(const FVector& Origin, const FVector& Direction)
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

FPlane UCsScriptLibrary_Math::MakePlane(const FVector& Origin, const FVector& Normal)
{
	bool NormalIsNormalized = true;

	if (!Normal.IsNormalized())
	{
		NormalIsNormalized = false;

		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Math::MakeRay_OriginAndDirection: Direction is NOT normalized."));
	}
	return FPlane(Origin, NormalIsNormalized ? Normal : Normal.GetSafeNormal());
}

#pragma endregion Plane

// Intersection
#pragma region

bool UCsScriptLibrary_Math::RayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection)
{
	using namespace NCsScriptLibraryMath::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RayPlaneIntersection : Context;

	typedef NCsMath::FLibrary MathLibrary;

	return MathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, OutT, OutIntersection);
}

#pragma endregion Intersection