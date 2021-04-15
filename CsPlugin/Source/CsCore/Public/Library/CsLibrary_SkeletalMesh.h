// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;
class USkeletalMesh;
class USkeletalMeshComponent;

namespace NCsSkeletalMesh
{
	/**
	* Library of function related to SkeletalMesh
	*/
	class CSCORE_API FLibrary
	{
	// Load
	#pragma region
	public:

		/**
		* Load the SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the SkeletalMesh to load.
		* @param Log
		* return			NiagaraSystem.
		*/
		static USkeletalMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the SkeletalMesh to load.
		* @param Log
		* return			Material Interface.
		*/
		static USkeletalMesh* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Bone
	#pragma region
	public:

		/**
		* Check if the Bone is valid for given SkeletalMeshComponent.
		* 
		* @param Context	The calling Context.
		* @param Component	SkeletalMeshComponent.
		* @param Bone		Bone to check exists for SkeletalMesh on SkeletalMeshComponent.
		* 
		* return			Whether the Bone is valid.
		*/
		static bool IsBoneValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone);


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
		* Check if the Socket is valid for given SkeletalMeshComponent.
		*
		* @param Context	The calling Context.
		* @param Component	SkeletalMeshComponent.
		* @param Socket		Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return			Whether the Socket is valid.
		*/
		static bool IsSocketValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket);

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