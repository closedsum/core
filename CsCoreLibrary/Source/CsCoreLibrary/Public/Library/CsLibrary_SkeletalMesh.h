// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class USkeletalMesh;
class USkeletalMeshComponent;
class USceneComponent;
class UAnimMontage;

namespace NCsSkeletalMesh
{
	/**
	* Library of function related to SkeletalMesh
	*/
	class CSCORELIBRARY_API FLibrary
	{
	#define LogWarning void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Load
	#pragma region
	public:

		/**
		* Load the SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the SkeletalMesh to load.
		* return			SkeletalMesh.
		*/
		static USkeletalMesh* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Safely load the SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the SkeletalMesh to load.
		* @param Log
		* return			SkeletalMesh.
		*/
		static USkeletalMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning);

		/**
		* Load the SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the SkeletalMesh to load.
		* return			SkeletalMesh.
		*/
		static USkeletalMesh* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a SkeletalMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the SkeletalMesh to load.
		* @param Log
		* return			SkeletalMesh.
		*/
		static USkeletalMesh* SafeLoad(const FString& Context, const FString& Path, LogWarning);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static USkeletalMesh* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogWarning);

	#pragma endregion Get

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
		static FVector3f GetBoneLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone);

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
		static FRotator3f GetBoneRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static FVector3f GetBoneNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static FVector3f GetSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket);

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
		static FRotator3f GetSocketRotationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

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
		static FVector3f GetSocketNormalChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

	#pragma endregion Socket

	public:

		/**
		* Check if the Bone or Socket is valid for given SkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				Whether the BoneOrSocket is valid.
		*/
		static bool IsBoneOrSocketValidChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Safely check if the Bone or Socket is valid for given SkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		* @param Log			(optional)
		*
		* return				Whether the BoneOrSocket is valid.
		*/
		static bool SafeIsBoneOrSocketValid(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket, LogWarning);

		/**
		* Check if the Bone or Socket is valid for given Component.
		* NOTE: Conditional check for Component being of type: USkeletalMeshComponent.
		* 
		* @param Context		The calling Context.
		* @param Component		SceneComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				Whether the BoneOrSocket is valid.
		*/
		static bool ConditionalIsBoneOrSocketValidChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket);

		/**
		* Check if the Bone or Socket is valid for given Component.
		* NOTE: Conditional check for Component being of type: USkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SceneComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		* @param Log			(optional)
		*
		* return				Whether the BoneOrSocket is valid.
		*/
		static bool ConditionalSafeIsBoneOrSocketValid(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket, LogWarning);

		/**
		* Get the Bone or Socket direction (rotation as vector) for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket direction.
		*/
		static FVector3f GetBoneOrSocketDirectionChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket direction (rotation as vector) for the given Component.
		* NOTE: Check Component is of type: USkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket direction.
		*/
		static FVector3f GetBoneOrSocketDirectionChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket location for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket location.
		*/
		static FVector3f GetBoneOrSocketLocationChecked(const FString& Context, USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket location for the given Component.
		* NOTE: Check Component is of type: USkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket location.
		*/
		static FVector3f GetBoneOrSocketLocationChecked(const FString& Context, USceneComponent* Component, const FName& BoneOrSocket);

	#undef LogWarning
	};
}