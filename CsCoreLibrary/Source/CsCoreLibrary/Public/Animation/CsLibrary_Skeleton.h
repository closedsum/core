// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class USkeletalMesh;
class UAnimationAsset;
class UClass;

namespace NCsSkeleton
{
	/**
	* Library of function related to USkeleton
	*/
	class CSCORELIBRARY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, UAnimationAsset* Anim, LogLevel);

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
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, UClass* AnimClass, LogLevel);

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
		static bool IsValid(const FString& Context, UClass* AnimClass, UAnimationAsset* Anim, LogLevel);

	#undef LogLevel
	};
}

using NCsSkeletonLibrary = NCsSkeleton::FLibrary;