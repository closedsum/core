// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class USkeletalMesh;
class UAnimationAsset;
class UClass;

namespace NCsSkeleton
{
	/**
	* Library of function related to USkeleton
	*/
	class CSCORE_API FLibrary
	{
	public:

		/**
		* Check if the Skeletons between Mesh and Anim are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return
		*/
		static bool IsValidChecked(const FString& Context, USkeletalMesh* Mesh, UAnimationAsset* Anim);

		/**
		* Check if the Skeletons between Mesh and Anim are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return			
		*/
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, UAnimationAsset* Anim, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Check if the Skeletons between Mesh and AnimClass are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return
		*/
		static bool IsValidChecked(const FString& Context, USkeletalMesh* Mesh, UClass* AnimClass);

		/**
		* Check if the Skeletons between Mesh and AnimClass are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return
		*/
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, UClass* AnimClass, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Check if the Skeletons between AnimClass and Anim are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return
		*/
		static bool IsValidChecked(const FString& Context, UClass* AnimClass, UAnimationAsset* Anim);

		/**
		* Check if the Skeletons between AnimClass and Anim are compatible.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Anim
		* @param Log
		* return
		*/
		static bool IsValid(const FString& Context, UClass* AnimClass, UAnimationAsset* Anim, void(*Log)(const FString&) = &FCsLog::Warning);
	};
}