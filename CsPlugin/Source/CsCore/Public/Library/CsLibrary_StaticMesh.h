// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;
class UStaticMesh;

namespace NCsStaticMesh
{
	/**
	* Library of function related to StaticMesh
	*/
	class CSCORE_API FLibrary
	{
	// Load
	#pragma region
	public:

		/**
		* Load the StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the StaticMesh to load.
		* return			StaticMesh.
		*/
		static UStaticMesh* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Safely load the StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load
	};
}