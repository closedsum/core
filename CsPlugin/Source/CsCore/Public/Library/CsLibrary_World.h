// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UWorld;
class UObject;

namespace NCsWorld
{
	class CSCORE_API FLibrary final
	{
	public:

		/**
		* Get World from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World
		*/
		static UWorld* GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get World from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log
		* return				World
		*/
		static UWorld* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get World from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World
		*/
		static UWorld* GetSafe(const UObject* WorldContext);

		static bool IsPlayInGame(UWorld* World);

		static bool IsPlayInEditor(UWorld* World);
	
		static bool IsPlayInPIE(UWorld* World);

		static bool IsPlayInEditorPreview(UWorld* World);

		static bool IsPlayInGameOrPIE(UWorld* World);

		static bool IsAnyWorldContextEditorOrEditorPreview();

		static bool IsEditorPreviewOrphaned(UObject* WorldContext);
	};
}