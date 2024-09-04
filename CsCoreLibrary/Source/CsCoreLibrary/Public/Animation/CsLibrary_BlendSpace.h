// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UBlendSpace;
class UBlendSpace1D;

namespace NCsBlendSpace
{
	/**
	* Library of function related to UBlendSpace
	*/
	class CSCORELIBRARY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
		static UBlendSpace* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Load a BlendSpace at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the BlendSpace to load.
		* @param Log
		* return			BlendSpace.
		*/
		static UBlendSpace* SafeLoad(const FString& Context, const FString& Path, LogLevel);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		/**
		* Get BlendSpace value associated with member at Path for Object.
		* 
		* @param Context	The calling context.
		* @param Object
		* @param Path
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			BlendSpace.
		*/
		static UBlendSpace* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Get

	#undef LogLevel
	};

	namespace N1D
	{
		/**
		* Library of function related to UBlendSpace1D
		*/
		class CSCORELIBRARY_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
			static UBlendSpace1D* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

			/**
			* Load a BlendSpace1D at the given Path.
			*
			* @param Context	The calling context.
			* @param Path		FString path to the BlendSpace1D to load.
			* @param Log
			* return			BlendSpace1D.
			*/
			static UBlendSpace1D* SafeLoad(const FString& Context, const FString& Path, LogLevel);

		#pragma endregion Load

		// Get
		#pragma region
		public:

			/**
			* Get BlendSpace1D value associated with member at Path for Object.
			* 
			* @param Context	The calling context.
			* @param Object
			* @param Path
			* @param OutSuccess	(out)
			* @param Log		(optional)
			* return			BlendSpace1D.
			*/
			static UBlendSpace1D* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

		#pragma endregion Get

		#undef LogLevel
		};
	}
}

using NCsBlendSpaceLibrary = NCsBlendSpace::FLibrary;