// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class AGameStateBase;
class UObject;

namespace NCsGameState
{
	class CSCORE_API FLibrary final
	{
	public:

		/**
		* Get GameState from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static AGameStateBase* GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get GameState from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log
		* return				GameState
		*/
		static AGameStateBase* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get GameState from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static AGameStateBase* GetSafe(const UObject* WorldContext);

		/**
		* Get GameState from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get GameState from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log
		* return				GameState
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get GameState from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static UObject* GetSafeAsObject(const UObject* WorldContext);
	};
}