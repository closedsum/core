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
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
		static USkeletalMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

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
		static USkeletalMesh* SafeLoad(const FString& Context, const FString& Path, LogLevel);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static USkeletalMesh* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Get

	// Asset
	#pragma region 
	public:

		static bool HasAssetChecked(const FString& Context, const USkeletalMeshComponent* Component);

		static bool SafeHasAsset(const FString& Context, const USkeletalMeshComponent* Component, LogLevel);

	#pragma endregion Asset
	
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
		static bool IsBoneValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone);

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
		static FVector GetBoneLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone);

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
		static FVector3f GetBoneLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone);

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
		static FRotator GetBoneRotationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static FRotator3f GetBoneRotation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static FVector GetBoneNormalChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static FVector3f GetBoneNormal3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Bone, const int32& Rules);

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
		static bool IsSocketValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket);

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
		static FVector GetSocketLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket);

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
		static FVector3f GetSocketLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket);

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
		static FRotator GetSocketRotationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

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
		static FRotator3f GetSocketRotation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

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
		static FVector GetSocketNormalChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

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
		static FVector3f GetSocketNormal3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& Socket, const int32& Rules);

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
		static bool IsBoneOrSocketValidChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket);

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
		static bool SafeIsBoneOrSocketValid(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, LogLevel);

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
		static bool ConditionalIsBoneOrSocketValidChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket);

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
		static bool ConditionalSafeIsBoneOrSocketValid(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket, LogLevel);

		/**
		* Get the Bone or Socket direction (rotation as vector) for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket direction.
		*/
		static FVector GetBoneOrSocketDirectionChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket direction (rotation as vector) for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket direction.
		*/
		static FVector3f GetBoneOrSocketDirection3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket);

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
		static FVector GetBoneOrSocketDirectionChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket);

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
		static FVector3f GetBoneOrSocketDirection3fChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket location for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket location.
		*/
		static FVector GetBoneOrSocketLocationChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Get the Bone or Socket location for the given Component.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		*
		* return				BoneOrSocket location.
		*/
		static FVector3f GetBoneOrSocketLocation3fChecked(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket);

		/**
		* Safely get the Bone or Socket location for the given Component.
		* NOTE: Check Component is of type: USkeletalMeshComponent.
		*
		* @param Context		The calling Context.
		* @param Component		SkeletalMeshComponent.
		* @param BoneOrSocket	Bone or Socket to check exists for SkeletalMesh on SkeletalMeshComponent.
		* @param OutSuccess		(out)
		* @param Log			(optional)
		*
		* return				BoneOrSocket location.
		*/
		static FVector GetSafeBoneOrSocketLocation(const FString& Context, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, bool& OutSuccess, LogLevel);

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
		static FVector GetBoneOrSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket);

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
		static FVector3f GetBoneOrSocketLocation3fChecked(const FString& Context, const USceneComponent* Component, const FName& BoneOrSocket);

	#undef LogLevel
	};
}