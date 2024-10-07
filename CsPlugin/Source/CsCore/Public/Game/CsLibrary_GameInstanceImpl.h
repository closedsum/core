// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UGameInstance;
class UCsGameInstance;

namespace NCsGameInstance
{
	namespace NImpl
	{
		class CSCORE_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &FCsLog::Warning

		public:

			static FString PrintObjectAndClass(const UGameInstance* Object);

			static FString PrintNameAndClass(const UGameInstance* Object);

		// Get
		#pragma region
		public:

			/**
			* Get GameInstance from ContextObject.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				GameInstance
			*/
			static UCsGameInstance* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get GameInstance from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* @param Log
			* return				GameInstance
			*/
			static UCsGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);
			FORCEINLINE static UCsGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel)
			{
				UCsGameInstance* GameInstance = GetSafe(Context, ContextObject, Log);
				OutSuccess					  = GameInstance != nullptr;
				return GameInstance;
			}

		#pragma endregion Get

		// Editor
		#pragma region
		public:

			/**
			* Check if the instance currently running is PIE.
			* NOTE: Assumes the GameInstance is of type: UCsGameInstance.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				Whether the instance running is PIE.
			*/
			static bool IsPIEChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Check if the instance currently running is simulating Mobile Preview in PIE.
			* NOTE: Assumes the GameInstance is of type: UCsGameInstance.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				Whether the instance running is simulating Mobile Preview in PIE.
			*/
			static bool IsMobilePIEChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Check if the instance currently running is Standalone from Editor.
			* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				Whether the instance running is Standalone from Editor.
			*/
			static bool IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Check if the instance currently running is Standalone Mobile from Editor.
			* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				Whether the instance running is Standalone Mobile from Editor.
			*/
			static bool IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Check if the instance currently running is a Mobile Preview with Editor (WITH_EDITOR == 1).
			* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				Whether the instance running is a Mobile Preview with Editor.
			*/
			static bool IsMobilePreviewEditorChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely check if the instance currently running is a Mobile Preview with Editor (WITH_EDITOR == 1).
			* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				Whether the instance running is a Mobile Preview with Editor.
			*/
			static bool SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, LogLevel);

		#pragma endregion Editor

		#undef LogLevel
		};
	}
}

using CsGameInstanceImplLibrary = NCsGameInstance::NImpl::FLibrary;