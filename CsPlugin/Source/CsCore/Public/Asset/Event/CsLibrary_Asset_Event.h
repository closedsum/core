// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Asset/Event/CsAsset_Event_Delegates.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class ICsAsset_Event;

namespace NCsAsset
{
	namespace NEvent
	{
		struct CSCORE_API FLibrary
		{
		// Get
		#pragma region
		public:

			/**
			* Get the interface: ICsAsset_Event from Object.
			* 
			* @param Context	The calling context.
			* @param Object
			* return			Interface of type: ICsAsset_Event.
			*/
			static ICsAsset_Event* GetChecked(const FString& Context, UObject* Object);
			
			/**
			* Get the interface: ICsAsset_Event from GEngine (Usually UUnrealEdEngine).
			*  GEngine must implement the interface: ICsAsset_Event.
			* 
			* @param Context	The calling context.
			* return			Interface of type: ICsAsset_Event
			*/
			static ICsAsset_Event* GetChecked(const FString& Context);

		#pragma endregion Get

		// Implements
		#pragma region
		public:

			static bool ImplementsChecked(const FString& Context, const UObject* Object);

			static bool SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Implements

		public:

			static NCsAsset::FOnOpenedInEditor& GetAsset_OpenedInEditor_EventChecked(const FString& Context);

			static NCsAsset::FOnUniqueOpenedInEditor& GetAsset_UniqueOpenedInEditor_EventChecked(const FString& Context);

			static NCsAsset::FOnRequest_Close& GetAssetEditor_OnRequest_Close_EventChecked(const FString& Context);

			static FCsAssetEditor_OnRequest_Close& GetAssetEditor_OnRequest_Close_ScriptEvent(const FString& Context);
		};
	}
}

using CsAssetEventLibrary = NCsAsset::NEvent::FLibrary;