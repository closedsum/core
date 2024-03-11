// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Asset/Tool/CsLibrary_GetAssetTool.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Asset/Tool/CsGetAssetTool.h"

namespace NCsAsset
{
	namespace NTool
	{
		// Get
		#pragma region

		ICsGetAssetTool* FLibrary::GetChecked(const FString& Context, UObject* Object)
		{
			return CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsGetAssetTool);
		}
			
		ICsGetAssetTool* FLibrary::GetChecked(const FString& Context)
		{
		#if WITH_EDITOR
			return GetChecked(Context, GEngine);
		#else
			check(0);
			return nullptr;
		#endif // #if WITH_EDITOR
		}

		#pragma endregion Get

		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsGetAssetTool);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsGetAssetTool)
			return true;
		}

		#pragma endregion Implements

		bool FLibrary::IsAssetOpened(const FString& Context, UObject* Asset)
		{
			return GetChecked(Context)->GetAssetTool()->IsAssetOpenedImpl(Asset);
		}
	}
}