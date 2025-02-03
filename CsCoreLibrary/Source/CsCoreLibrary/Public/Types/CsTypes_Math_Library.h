// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

// RotationRules
#pragma region

class AActor;
class USceneComponent;
class USkeletalMeshComponent;

namespace NCsRotationRules
{
	/**
	* Get the Rotation filtered by the bit mask, Rules.
	*
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator3f GetRotation(const FRotator3f& InRotation, const int32& Rules)
	{
		FRotator3f Rotation = InRotation;

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	*
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator3d GetRotation(const FRotator3d& InRotation, const int32& Rules)
	{
		FRotator3d Rotation = InRotation;

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0;

		return Rotation;
	}

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	*
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator3f GetRotation3f(const FRotator3d& InRotation, const int32& Rules)
	{
		FRotator3f Rotation((float)InRotation.Pitch, (float)InRotation.Yaw, (float)InRotation.Roll);

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	* Check Rules has at least 1 bit flag set.
	* 
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator GetRotationChecked(const FString& Context, FRotator Rotation, const int32& Rules)
	{
		checkf(Rules != None, TEXT("%s: Rules == 0. No bit flags set."), *Context);

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	/**
	* Get the Rotation filtered by the bit mask, Rules.
	* Check Rules has at least 1 bit flag set.
	* 
	* @param Rotation
	* @param Rules		 Bit mask for which components of the Rotation to return.
	*
	* return			Rotation filtered by the bit mask, Rules.
	*/
	FORCEINLINE FRotator3f GetRotationChecked(const FString& Context, FRotator3f Rotation, const int32& Rules)
	{
		checkf(Rules != None, TEXT("%s: Rules == 0. No bit flags set."), *Context);

		Rotation.Pitch = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Rotation.Pitch : 0.0f;
		Rotation.Yaw   = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Rotation.Yaw : 0.0f;
		Rotation.Roll  = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Roll) ? Rotation.Roll : 0.0f;

		return Rotation;
	}

	/**
	* Get the rotation of Actor filtered by the bit mask, Rules. 
	*
	* @param Actor
	* @param Rules	Bit mask for which components of the Actor's rotation to return.
	*
	* return		Actor's rotation filtered by the bit mask, Rules. 
	*/
	CSCORELIBRARY_API FRotator3f GetRotation3f(AActor* Actor, const int32& Rules);

	/**
	* Get the rotation of Actor filtered by the bit mask, Rules. 
	*
	* @param Actor
	* @param Rules	Bit mask for which components of the Actor's rotation to return.
	*
	* return		Actor's rotation filtered by the bit mask, Rules. 
	*/
	CSCORELIBRARY_API FRotator3d GetRotation3d(AActor* Actor, const int32& Rules);
	FORCEINLINE FRotator GetRotation(AActor* Actor, const int32& Rules) { return GetRotation3d(Actor, Rules); }

	/**
	* Get the rotation of Component filtered by the bit mask, Rules.
	*
	* @param Component
	* @param Rules		Bit mask for which components of the Component's rotation to return.
	*
	* return			Component's rotation filtered by the bit mask, Rules.
	*/
	CSCORELIBRARY_API FRotator3f GetRotation3f(USceneComponent* Component, const int32& Rules);

	/**
	* Get the rotation of Component filtered by the bit mask, Rules.
	*
	* @param Component
	* @param Rules		Bit mask for which components of the Component's rotation to return.
	*
	* return			Component's rotation filtered by the bit mask, Rules.
	*/
	CSCORELIBRARY_API FRotator3d GetRotation3d(USceneComponent* Component, const int32& Rules);
	FORCEINLINE FRotator GetRotation(USceneComponent* Component, const int32& Rules) { return GetRotation3d(Component, Rules); }

	FORCEINLINE FVector3f GetDirection(FVector3f Direction, const int32& Rules)
	{
		Direction.X = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.X : 0.0f;
		Direction.Y = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.Y : 0.0f;
		Direction.Z = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Direction.Z : 0.0f;

		return Direction;
	}

	FORCEINLINE FVector3d GetDirection(FVector3d Direction, const int32& Rules)
	{
		Direction.X = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.X : 0.0;
		Direction.Y = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Yaw) ? Direction.Y : 0.0;
		Direction.Z = CS_TEST_BLUEPRINT_BITFLAG(Rules, Type::Pitch) ? Direction.Z : 0.0;

		return Direction;
	}

	// NOTE: FUTURE: This can potentially be optimized based on rules
	FORCEINLINE FVector3f GetDirection(FRotator3f Rotation, const int32& Rules)
	{
		return GetDirection(Rotation.Vector(), Rules);
	}

	FORCEINLINE FVector3d GetDirection(FRotator3d Rotation, const int32& Rules)
	{
		return GetDirection(Rotation.Vector(), Rules);
	}
}

#pragma endregion RotationRules

// TransformRules
#pragma region

class USceneComponent;
class AActor;

namespace NCsTransformRules
{
	/**
	* Set the relative transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetRelativeTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules);

	/**
	* Set the relative transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetRelativeTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules);

	/**
	* Set the relative transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules. 
	* 
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetRelativeTransform(AActor* Actor, const FTransform3d& Transform, const int32& Rules);
	
	/**
	* Set the relative transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetRelativeTransform(AActor* Actor, const FTransform3f& Transform, const int32& Rules);

	/**
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules);

	/**
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules);

	/**
	* Set the transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetTransform(AActor* Actor, const FTransform3d& Transform, const int32& Rules);

	/**
	* Set the transform of an Actor to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Actor
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	*/
	CSCORELIBRARY_API void SetTransform(AActor* Actor, const FTransform3f& Transform, const int32& Rules);

	/**
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* @param Spaces
	*/
	CSCORELIBRARY_API void SetTransform(USceneComponent* Component, const FTransform3d& Transform, const int32& Rules, const ECsTransformSpace(&Spaces)[(uint8)ECsTransform::ECsTransform_MAX]);

	/**
	* Set the transform of a SceneComponent to Transform based on some Rules,
	* which determine which component of the Transform to use.
	* See ECsTransformRules.
	*
	* @param Component
	* @param Transform
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* @param Spaces
	*/
	CSCORELIBRARY_API void SetTransform(USceneComponent* Component, const FTransform3f& Transform, const int32& Rules, const ECsTransformSpace(&Spaces)[(uint8)ECsTransform::ECsTransform_MAX]);

	/**
	* Compare transforms A and B with Rules to determine which components are equal.
	* 
	* @param A
	* @oaran B
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* return
	*/
	CSCORELIBRARY_API bool AreTransformsEqual(const FTransform3d& A, const FTransform3d& B, const int32& Rules);

	/**
	* Compare transforms A and B with Rules to determine which components are equal.
	*
	* @param A
	* @oaran B
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* return
	*/
	CSCORELIBRARY_API bool AreTransformsEqual(const FTransform3f& A, const FTransform3f& B, const int32& Rules);

	/**
	* Compare transforms A and B with Rules to determine which components are equal.
	*
	* @param A
	* @oaran B
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* return
	*/
	CSCORELIBRARY_API bool AreTransformsEqual(const FTransform3f& A, const FTransform3d& B, const int32& Rules);

	/**
	* Compare transforms A and B with Rules to determine which components are equal.
	*
	* @param A
	* @oaran B
	* @param Rules		Bit mask using the bit flag ECsTransformRules.
	* return
	*/
	CSCORELIBRARY_API bool AreTransformsEqual(const FTransform3d& A, const FTransform3f& B, const int32& Rules);
}

#pragma endregion TransformRules