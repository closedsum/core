// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsInput
{
	class CSCORE_API FLibrary
	{
	public:

		/**
		*
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*/
		static void ShowMouseCursorChecked(const FString& Context, UObject* WorldContext);

		/**
		*
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*/
		static void HideMouseCursorChecked(const FString& Context, UObject* WorldContext);

		/**
		* 
		* 
		* @param Context		The calling context
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*/
		static void SetMouseCenterOfViewportChecked(const FString& Context, UObject* WorldContext);
	};
}