// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UAnimSequence;

namespace NCsAnimSequence
{
	/**
	* Library of function related to UAnimSequence
	*/
	class CSCORE_API FLibrary
	{
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
		static UAnimSequence* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a AnimSequence at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimSequence to load.
		* @param Log
		* return			AnimSequence.
		*/
		static UAnimSequence* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static UAnimSequence* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Get
	};
}