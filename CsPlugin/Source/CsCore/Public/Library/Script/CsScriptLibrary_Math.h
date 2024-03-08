// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

// Int
#pragma region
public:

	/** Returns true if A is greater than B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "integer > integer (Checked)", CompactNodeTitle = ">", Keywords = "> greater", AutoCreateRefTerm = "Context,A,B"))
	static bool GreaterChecked_IntInt(const FString& Context, const int32& A, const int32& B);

	/** Returns true if A is greater than or equal to B (A >= B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "integer >= integer (Checked)", CompactNodeTitle = ">=", Keywords = ">= greater", AutoCreateRefTerm = "Context,A,B"))
	static bool GreaterEqualChecked_IntInt(const FString& Context, const int32& A, const int32& B);
	
	/** Returns true if A is less than B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "integer < integer (Checked)", CompactNodeTitle = "<", Keywords = "< less", AutoCreateRefTerm = "Context,A,B"))
	static bool LessChecked_IntInt(const FString& Context, const int32& A, const int32& B);

	/** Returns true if A is less than or equal to B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "integer <= integer (Checked)", CompactNodeTitle = "<=", Keywords = "<= less", AutoCreateRefTerm = "Context,A,B"))
	static bool LessEqualChecked_IntInt(const FString& Context, const int32& A, const int32& B);

#pragma endregion Int

// Float
#pragma region
public:

	/** Returns true if A is greater than B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "float > float (Checked)", CompactNodeTitle = ">", Keywords = "> greater", AutoCreateRefTerm = "Context,A,B"))
	static bool GreaterChecked_FloatFloat(const FString& Context, const float& A, const float& B);

	/** Returns true if A is greater than or equal to B (A >= B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "float >= float (Checked)", CompactNodeTitle = ">=", Keywords = ">= greater", AutoCreateRefTerm = "Context,A,B"))
	static bool GreaterEqualChecked_FloatFloat(const FString& Context, const float& A, const float& B);
	
	/** Returns true if A is less than B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "float < float (Checked)", CompactNodeTitle = "<", Keywords = "< less", AutoCreateRefTerm = "Context,A,B"))
	static bool LessChecked_FloatFloat(const FString& Context, const float& A, const float& B);

	/** Returns true if A is less than or equal to B (A > B) and ASSERT if NOT. */
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math", meta = (DisplayName = "float <= float (Checked)", CompactNodeTitle = "<=", Keywords = "<= less", AutoCreateRefTerm = "Context,A,B"))
	static bool LessEqualChecked_FloatFloat(const FString& Context, const float& A, const float& B);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math", meta = (AutoCreateRefTerm = "TheFloat,Precision"))
	static FString GetFloatAsStringWithPrecision(const float& TheFloat, const uint8& Precision);

#pragma endregion Float

// Easing
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math", meta = (AutoCreateRefTerm = "Context,EasingType,Time,Start,Final,Duration"))
	static float Ease(const FString& Context, const ECsEasingType& EasingType, const float& Time, const float& Start, const float& Final, const float& Duration);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Math", meta = (AutoCreateRefTerm = "Context,EasingType,TimeAsPercent,Start,Final"))
	static float EasePercent(const FString& Context, const ECsEasingType& EasingType, const float& TimeAsPercent, const float& Start, const float& Final);

#pragma endregion Easing

// Vector
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Vector"))
	static FVector3f Vector3dTo3f(const FVector& Vector);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Vector"))
	static FVector Vector3fTo3d(const FVector3f& Vector);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Yaw"))
	static FVector Forward3d_OnlyYaw(const double& Yaw);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Yaw"))
	static FVector3f Forward3f_OnlyYaw(const float& Yaw);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Yaw"))
	static FVector Right3d_OnlyYaw(const double& Yaw);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Yaw"))
	static FVector3f Right3f_OnlyYaw(const float& Yaw);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Normal"))
	static FVector3f Vector3f_Right3f_FromNormal(const FVector3f& Normal);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Normal"))
	static FVector Vector3d_Right3d_FromNormal(const FVector& Normal);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Vector"))
	static FVector3f Vector3f_Right3f(const FVector3f& Vector);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Vector"))
	static FVector Vector3d_Right3d(const FVector& Vector);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Normal,OutRotation"))
	static FVector3f Vector3f_Right3f_FromNormal2D(const FVector3f& Normal, FRotator3f& OutRotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Vector", meta = (AutoCreateRefTerm = "Normal,OutRotation"))
	static FVector Vector3d_Right3d_FromNormal2D(const FVector& Normal, FRotator& OutRotation);

#pragma endregion Vector

// Rotation
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector3f Rotator3d_Forward3f_OnlyYaw(const FRotator& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector Rotator3d_Forward3d_OnlyYaw(const FRotator& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector3f Rotator3f_Forward3f_OnlyYaw(const FRotator3f& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector Rotator3f_Forward3d_OnlyYaw(const FRotator3f& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector3f Rotator3d_Right3f_OnlyYaw(const FRotator& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector Rotator3d_Right3d_OnlyYaw(const FRotator& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector3f Rotator3f_Right3f_OnlyYaw(const FRotator3f& Rotation);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Rotation", meta = (AutoCreateRefTerm = "Rotation"))
	static FVector Rotator3f_Right3d_OnlyYaw(const FRotator3f& Rotation);

#pragma endregion Rotation

// Matrix
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Matrix", meta = (AutoCreateRefTerm = "Rotation,Axis"))
	static FVector RotationMatrix44d_UnitAxis(const FRotator& Rotation, const TEnumAsByte<EAxis::Type>& Axis);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Matrix", meta = (AutoCreateRefTerm = "Yaw,Axis"))
	static FVector RotationMatrix44d_Yaw_UnitAxis(const float& Yaw, const TEnumAsByte<EAxis::Type>& Axis);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Matrix", meta = (AutoCreateRefTerm = "Rotation,Axis"))
	static FVector RotationMatrix44d_UnitAxis_OnlyYaw(const FRotator& Rotation, const TEnumAsByte<EAxis::Type>& Axis);

#pragma endregion Matrix

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
	static FCsRay MakeRay(const FVector3f& Origin, const FVector3f& Direction, const float& Distance);

	/*
	* Make a Ray from origin and direction.
	* Assume distance is a very large value.
	* 
	* @param Origin
	* @param Direction
	* return			Ray
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Math|Ray", meta = (Keywords = "construct build", NativeMakeFunc, AutoCreateRefTerm = "Origin,Direction"))
	static FCsRay MakeRay_OriginAndDirection(const FVector3f& Origin, const FVector3f& Direction);

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
	static FPlane4f MakePlane(const FVector3f& Origin, const FVector3f& Normal);

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
	static bool RayPlaneIntersection(const FString& Context, const FCsRay& Ray, const FPlane4f& Plane, float& OutT, FVector3f& OutIntersection);

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