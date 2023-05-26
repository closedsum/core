// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;
class UTexture;

namespace NCsTexture
{
	/**
	* Library of function related to Texture
	*/
	class CSCORE_API FLibrary
	{
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
		static UTexture* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static UTexture* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load
	};
}