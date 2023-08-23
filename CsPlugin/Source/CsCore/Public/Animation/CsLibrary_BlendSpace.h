// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UBlendSpace;
class UBlendSpace1D;

namespace NCsBlendSpace
{
	/**
	* Library of function related to UBlendSpace
	*/
	class CSCORE_API FLibrary
	{
	// Load
	#pragma region
	public:

		/**
		* Load the BlendSpace at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the BlendSpace to load.
		* @param Log
		* return			BlendSpace.
		*/
		static UBlendSpace* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a BlendSpace at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the BlendSpace to load.
		* @param Log
		* return			BlendSpace.
		*/
		static UBlendSpace* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load
	};

	namespace N1D
	{
		/**
		* Library of function related to UBlendSpace1D
		*/
		class CSCORE_API FLibrary
		{
		// Load
		#pragma region
		public:

			/**
			* Load the BlendSpace1D at the given Path.
			*
			* @param Context	The calling context.
			* @param Path		SoftObjectPath to the BlendSpace1D to load.
			* @param Log
			* return			BlendSpace1D.
			*/
			static UBlendSpace1D* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Load a BlendSpace1D at the given Path.
			*
			* @param Context	The calling context.
			* @param Path		FString path to the BlendSpace1D to load.
			* @param Log
			* return			BlendSpace1D.
			*/
			static UBlendSpace1D* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Load
	};
	}
}