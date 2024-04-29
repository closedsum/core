// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UActorComponent;

namespace NCsActorComponent
{
	/**
	* Library of functions related to UActorComponent
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define LogWarning void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		/**
		* Get the Components that have ComponentTags that contain Tags.
		* 
		* @param Context		The calling context.
		* @param Components
		* @param Names
		* @param OutComponents	(out)
		*/
		static void GetChecked(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents);

		/**
		* Safely get the Components that have ComponentTags that contain Tags.
		* 
		* @param Context		The calling context.
		* @param Components
		* @param Names
		* @param OutComponents	(out)
		* @param Log			(optional)
		* return				Whether any Components were found that have ComponentTags that contain Tags.
		*/
		static bool GetSafe(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents, LogWarning);

	#undef LogWarning
	};
}