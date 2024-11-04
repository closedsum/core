// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "UObject/SoftObjectPtr.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UBlueprint;
class UBlueprintGeneratedClass;

namespace NCsBlueprint
{
	/**
	* Library of function related to UBlueprint
	*/
	class CSCORELIBRARY_API FLibrary final
	{
	private:

		CS_DECLARE_STATIC_LOG_LEVEL

	// Load
	#pragma region
	public:

		/**
		* Load the Blueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Blueprint to load.
		* return			Blueprint.
		*/
		FORCEINLINE static UBlueprint* LoadChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint) 
		{
			return LoadChecked(Context, Blueprint.ToSoftObjectPath());
		}

		/**
		* Load the Blueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Blueprint to load.
		* return			Blueprint.
		*/
		static UBlueprint* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Load the Blueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Blueprint to load.
		* @param Log		(optional)
		* return			Blueprint.
		*/
		static UBlueprint* SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		/**
		* Load a Blueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Blueprint to load.
		* return			Blueprint.
		*/
		static UBlueprint* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Load a Blueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Blueprint to load.
		* @param Log		(optional)
		* return			Blueprint.
		*/
		static UBlueprint* SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UBlueprintGeneratedClass* LoadClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, const FString& Path);

		static UBlueprintGeneratedClass* GetSafeClass(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint);

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, UBlueprint* Blueprint);

		static UBlueprintGeneratedClass* GetSafeClass(const FString& Context, UBlueprint* Blueprint, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UBlueprintGeneratedClass* GetSafeClass(UObject* Blueprint);

		static UObject* GetSafeClassDefaultObject(const FString& Context, UBlueprint* Blueprint, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UObject* GetSafeClassDefaultObject(const FString& Context, UObject* Blueprint, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UObject* GetSafeClassDefaultObject(UObject* Blueprint);

		static UObject* GetSafeDefaultObject(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UObject* GetSafeDefaultObject(const FString& Context, UBlueprint* Blueprint, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UObject* GetSafeDefaultObject(const FString& Context, UObject* Blueprint, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static UObject* GetSafeDefaultObject(UObject* Blueprint);

	#pragma endregion Get

	// Is
	#pragma region

		static bool Is(const UObject* Object);

		static bool SafeIs(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

	#pragma endregion

	// Spawn
	#pragma region
	public:

		static AActor* SpawnAsActorChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UBlueprint>& Blueprint);

	#pragma endregion Spawn
	};
}

using CsBlueprintLibrary = NCsBlueprint::FLibrary;