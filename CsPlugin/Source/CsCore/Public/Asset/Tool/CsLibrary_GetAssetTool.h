// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class ICsGetAssetTool;

namespace NCsAsset
{
	namespace NTool
	{
		struct CSCORE_API FLibrary
		{
		// Get
		#pragma region
		public:

			/**
			* Get the interface: ICsGetAssetTool from Object.
			* 
			* @param Context	The calling context.
			* @param Object
			* return			Interface of type: ICsGetAssetTool.
			*/
			static ICsGetAssetTool* GetChecked(const FString& Context, UObject* Object);
			
			/**
			* Get the interface: ICsGetAssetTool from GEngine (Usually UUnrealEdEngine).
			*  GEngine must implement the interface: ICsGetAssetTool.
			* 
			* @param Context	The calling context.
			* return			Interface of type: ICsGetAssetTool
			*/
			static ICsGetAssetTool* GetChecked(const FString& Context);

		#pragma endregion Get

		// Implements
		#pragma region
		public:

			static bool ImplementsChecked(const FString& Context, const UObject* Object);

			static bool SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Implements

		public:

			static bool IsAssetOpened(const FString& Context, UObject* Asset);

			static bool IsAssetWithClassDefaultOpened(const FString& Context, UObject* DefaultObject);
		};
	}
}