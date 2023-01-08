// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Interpolation.h"

#include "CsScriptLibrary_Math.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Math : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math", meta = (AutoCreateRefTerm = "TheFloat,Precision"))
	static FString GetFloatAsStringWithPrecision(const float& TheFloat, const uint8& Precision);

// Easing
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math", meta = (AutoCreateRefTerm = "Context,EasingType,Time,Start,Final,Duration"))
	static float Ease(const FString& Context, const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration);

#pragma endregion Easing

// Ray
#pragma region
public:
	
	/**
	* Make a Ray from origin, direction, and distance.
	* 
	* @param Origin
	* @param Direction
	* @param Distance
	* return			Ray
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Ray", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Origin,Direction,Distance"))
	static FCsRay MakeRay(const FVector& Origin, const FVector& Direction, const float& Distance);

	/*
	* Make a Ray from origin and direction.
	* Assume distance is a very large value.
	* 
	* @param Origin
	* @param Direction
	* return			Ray
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Ray", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Origin,Direction"))
	static FCsRay MakeRay_OriginAndDirection(const FVector& Origin, const FVector& Direction);

#pragma endregion Ray

// Plane
#pragma region
public:

	/**
	* Make a Plane from origin and normal.
	*
	* @param Origin
	* @param Normal
	* return		Plane
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Plane", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Origin,Normal"))
	static FPlane MakePlane(const FVector& Origin, const FVector& Normal);

#pragma endregion Plane

// Intersection
#pragma region
public:

	/**
	* Computes the intersection point between a ray and a plane.
	*
	* @param Context			The calling context.
	* @param Ray				The t of the intersection between the line and the plane.
	* @param Plane
	* @param OutT				(out)
	* @param OutIntersection	(out) The point of intersection between the line and the plane.
	* return					True if the intersection test was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math|Intersection", meta = (AutoCreateRefTerm = "Context,Ray,Plane,OutT,OutIntersection"))
	static bool RayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane& Plane, float& OutT, FVector& OutIntersection);

#pragma endregion Intersection

// Transform
#pragma region
public:

	/**
	* Make a Identity Transform.
	*
	* return Identity Transform
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Transform")
	static FTransform MakeTransform_Identity()
	{
		return FTransform::Identity;
	}

#pragma endregion Transform

// Rotation
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation")
	static int32 MakeRotationRules_Pitch() { return 1; /* 1 << (int32)(ECsRotationRules::Pitch) */ }

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation")
	static int32 MakeRotationRules_Yaw() { return 2; /* 1 << (int32)(ECsRotationRules::Yaw) */ }

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation")
	static int32 MakeRotationRules_Roll() { return 4; /* 1 << (int32)(ECsRotationRules::Pitch) */ }

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation")
	static int32 MakeRotationRules_All() { return 7; /* 1 + 2 + 4 */ }

#pragma endregion Rotation
};