// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

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
	};
}