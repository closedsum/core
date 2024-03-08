// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Asset/Event/CsLibrary_Asset_Event.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Asset/Event/CsAsset_Event.h"
// Engine
#include "Engine/Engine.h"

namespace NCsAsset
{
	namespace NEvent
	{
		// Get
		#pragma region

		ICsAsset_Event* FLibrary::GetChecked(const FString& Context, UObject* Object)
		{
			return CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsAsset_Event);
		}
			
		ICsAsset_Event* FLibrary::GetChecked(const FString& Context)
		{
			return GetChecked(Context, GEngine);
		}

		#pragma endregion Get

		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsAsset_Event);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsAsset_Event)
			return true;
		}

		#pragma endregion Implements

		NCsAsset::FOnOpenedInEditor& FLibrary::GetAsset_OpenedInEditor_EventChecked(const FString& Context)
		{
			return GetChecked(Context)->GetAsset_OpenedInEditor_Event();
		}

		NCsAsset::FOnUniqueOpenedInEditor& FLibrary::GetAsset_UniqueOpenedInEditor_EventChecked(const FString& Context)
		{
			return GetChecked(Context)->GetAsset_UniqueOpenedInEditor_Event();
		}

		NCsAsset::FOnRequest_Close& FLibrary::GetAssetEditor_OnRequest_Close_EventChecked(const FString& Context)
		{
			return GetChecked(Context)->GetAssetEditor_OnRequest_Close_Event();
		}

		FCsAssetEditor_OnRequest_Close& FLibrary::GetAssetEditor_OnRequest_Close_ScriptEvent(const FString& Context)
		{
			return GetChecked(Context)->GetAssetEditor_OnRequest_Close_ScriptEvent();
		}
	}
}