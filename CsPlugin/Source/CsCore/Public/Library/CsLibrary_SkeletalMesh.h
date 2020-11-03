// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
class USkeletalMeshComponent;

namespace NCsSkeletalMesh
{
	/**
	* Library of function related to SkeletalMesh
	*/
	class CSCORE_API FLibrary
	{
	public:

	// Bone
	#pragma region
	public:

		/**
		* Get the Bone's location from a SkeletalMeshComponent.
		* Check the Component and Bone are valid.
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Bone from which to retrieve the location.
		*
		* return			Bone's Location.
		*/
		static FVector GetBoneLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone);

		/**
		* Get the Bone's rotation from a SkeletalMeshComponent.
		* Check: 
		*  Component is Valid.
		*  Bone is Valid.
		*  Rules has at Least 1 bit flag set. 
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Bone from which to retrieve the rotation.
		* @param Rules		Bit mask for which components of the rotation to return.
		*					See ECsRotationRules. 
		*
		* return			Bone's Rotation.
		*/
		static FRotator GetBoneRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

		/**
		* Get the Bone's normal from a SkeletalMeshComponent.
		* Check: 
		*  Component is Valid.
		*  Bone is Valid.
		*  Rules has at Least 1 bit flag set. 
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Bone from which to retrieve the normal.
		* @param Rules		Bit mask for which components of the rotation use when returning the normal.
		*					See ECsRotationRules. 
		*
		* return			Bone's Normal.
		*/
		static FVector GetBoneNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

	#pragma endregion Bone

	// Socket
	#pragma region
	public:

		/**
		* Get the Socket's location from a SkeletalMeshComponent.
		* Check the Component and Socket are valid.
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Socket		Socket from which to retrieve the location.
		*
		* return			Socket's Location.
		*/
		static FVector GetSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket);

		/**
		* Get the Socket's rotation from a SkeletalMeshComponent.
		* Check: 
		*  Component is Valid.
		*  Bone is Valid.
		*  Rules has at Least 1 bit flag set. 
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Socket from which to retrieve the rotation.
		* @param Rules		Bit mask for which components of the rotation to return.
		*					See ECsRotationRules. 
		*
		* return			Socket's Rotation.
		*/
		static FRotator GetSocketRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

		/**
		* Get the Bone's normal from a SkeletalMeshComponent.
		* Check: 
		*  Component is Valid.
		*  Socket is Valid.
		*  Rules has at Least 1 bit flag set. 
		*
		* @param Context	The calling context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Socket from which to retrieve the normal.
		* @param Rules		Bit mask for which components of the rotation use when returning the normal.
		*					See ECsRotationRules. 
		*
		* return			Socket's Normal.
		*/
		static FVector GetSocketNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

	#pragma endregion Socket
	};
}