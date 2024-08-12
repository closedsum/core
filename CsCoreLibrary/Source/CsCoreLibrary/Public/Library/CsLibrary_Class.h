// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "UObject/SoftObjectPath.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UClass;

namespace NCsClass
{
	/**
	*/
	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Load
	#pragma region
	public:

		/**
		* Load a Class at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Class to load.
		* return			Class.
		*/
		static UClass* LoadChecked(const FString& Context, const FSoftObjectPath& Path);


		/**
		* Safely load a Class at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Class to load.
		* @param Log
		* return			Class.
		*/
		static UClass* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Load a Class at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Class to load.
		* return			Class.
		*/
		static UClass* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a Class at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Class to load.
		* @param Log
		* return			Class.
		*/
		static UClass* SafeLoad(const FString& Context, const FString& Path, LogLevel);

		/**
		* Safely load the Default Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Object to load.
		* @param Log		(optional)
		* @param OutSuccess	(out)
		* return			Object.
		*/
		static UObject* SafeLoadDefaultObject(const FString& Context, const FSoftObjectPath& Path, bool& OutSuccess, LogLevel);
		FORCEINLINE static UObject* SafeLoadDefaultObject(const FString& Context, const FSoftObjectPath& Path, LogLevel)
		{
			bool OutSuccess = false;
			return SafeLoadDefaultObject(Context, Path, OutSuccess, Log);
		}

		/**
		* Safely load the Default Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Object to load.
		* @param Log		(optional)
		* @param OutSuccess (out)
		* return			Object.
		*/
		static UObject* SafeLoadDefaultObject(const FString& Context, const FString& Path, bool& OutSuccess, LogLevel);
		FORCEINLINE static UObject* SafeLoadDefaultObject(const FString& Context, const FString& Path, LogLevel)
		{
			bool OutSuccess = false;
			return SafeLoadDefaultObject(Context, Path, OutSuccess, Log);
		}

	#pragma endregion Load

	#undef LogLevel
	};
}

using CsClassLibrary = NCsClass::FLibrary;