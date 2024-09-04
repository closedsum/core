// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UAnimSequence;

namespace NCsAnimSequence
{
	/**
	* Library of function related to UAnimSequence
	*/
	class CSCORELIBRARY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Load
	#pragma region
	public:

		/**
		* Load the AnimSequence at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the AnimSequence to load.
		* @param Log
		* return			AnimSequence.
		*/
		static UAnimSequence* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Load a AnimSequence at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimSequence to load.
		* @param Log
		* return			AnimSequence.
		*/
		static UAnimSequence* SafeLoad(const FString& Context, const FString& Path, LogLevel);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		/**
		* Get Anim Sequence value associated with member at Path for Object.
		* 
		* @param Context	The calling context.
		* @param Object
		* @param Path
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			Anim Sequence.
		*/
		static UAnimSequence* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Get

	#undef LogLevel
	};
}

using CsAnimSequenceLibrary = NCsAnimSequence::FLibrary;