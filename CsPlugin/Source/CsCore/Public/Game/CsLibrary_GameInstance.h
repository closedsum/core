// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UGameInstance;
class UObject;

namespace NCsGameInstance
{
	class CSCORE_API FLibrary final
	{
	public:

		/**
		* Get GameInstance from ContextObject.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				World
		*/
		static UGameInstance* GetChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely get GameInstance from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				World
		*/
		static UGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				World
		*/
		static UGameInstance* GetSafe(const UObject* ContextObject);
	};
}