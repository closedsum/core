// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UBlueprint;
class UBlueprintGeneratedClass;

namespace NCsBlueprint
{
	/**
	* Library of function related to UBlueprint
	*/
	class CSCORE_API FLibrary final
	{
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
		static UBlueprint* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static UBlueprint* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		static UBlueprintGeneratedClass* LoadClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, const FString& Path);

		static UBlueprintGeneratedClass* GetSafeClass(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, const TSoftObjectPtr<UBlueprint>& Blueprint);

		static UBlueprintGeneratedClass* GetClassChecked(const FString& Context, UBlueprint* Blueprint);

		static UBlueprintGeneratedClass* GetSafeClass(const FString& Context, UBlueprint* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		static UBlueprintGeneratedClass* GetSafeClass(UObject* Blueprint);

		static UObject* GetSafeClassDefaultObject(const FString& Context, UBlueprint* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		static UObject* GetSafeClassDefaultObject(const FString& Context, UObject* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		static UObject* GetSafeClassDefaultObject(UObject* Blueprint);

		static UObject* GetSafeDefaultObject(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		static UObject* GetSafeDefaultObject(const FString& Context, UBlueprint* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		static UObject* GetSafeDefaultObject(const FString& Context, UObject* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		static UObject* GetSafeDefaultObject(UObject* Blueprint);

	#pragma endregion Get

	// Is
	#pragma region

		static bool Is(const UObject* Object);

		static bool SafeIs(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion

	// Spawn
	#pragma region
	public:

		static AActor* SpawnAsActorChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UBlueprint>& Blueprint);

	#pragma endregion Spawn
	};
}