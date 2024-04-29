// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UTexture;

namespace NCsTexture
{
	/**
	* Library of function related to Texture
	*/
	class CSCORELIBRARY_API FLibrary
	{
	#define LogWarning void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Load
	#pragma region
	public:

		/**
		* Load the Texture at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Texture to load.
		* return			Texture.
		*/
		static UTexture* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Safely load the Texture at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Texture to load.
		* @param Log
		* return			Texture.
		*/
		static UTexture* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogWarning);

		/**
		* Load a Texture at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Texture to load.
		* @param Log
		* return			Texture.
		*/
		static UTexture* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a Texture at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Texture to load.
		* @param Log
		* return			Texture.
		*/
		static UTexture* SafeLoad(const FString& Context, const FString& Path, LogWarning);

	#pragma endregion Load

	#undef LogWarning
	};
}