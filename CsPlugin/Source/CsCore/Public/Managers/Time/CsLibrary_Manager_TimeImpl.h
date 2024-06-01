// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Update.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_TimeImpl;

namespace NCsTime
{
	namespace NManager
	{
		namespace NImpl
		{
			struct CSCORE_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &FCsLog::Warning

			// Get
			#pragma region
			public:

				/**
				* Get the reference to UCsManager_TimeImpl from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				UCsManager_TimeImpl.
				*/
				static UCsManager_TimeImpl* GetChecked(const FString& Context, const UObject* ContextObject);

				/**
				* Safely get the reference to UCsManager_TimeImpl from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log
				* return				UCsManager_TimeImpl.
				*/
				static UCsManager_TimeImpl* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

				/**
				* Safely get the reference to UCsManager_TimeImpl from a ContextObject.
				*
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				UCsManager_TimeImpl.
				*/
				static UCsManager_TimeImpl* GetSafe(const UObject* ContextObject);

			#pragma endregion Get

			// Time
			#pragma region
			public:

				/**
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						or
				*						A reference to the GameInstance.
				* @param Group
				* @param DeltaTime
				*/
				static void UpdateTimeAndCoroutineScheduler(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime);

			#pragma endregion Time

			#undef LogLevel
			};
		}
	}
}