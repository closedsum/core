// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "InputCoreTypes.h"

class UObject;

namespace NCsInput
{
	namespace NMouse
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Check if the mouse cursor is being shown. This checks bShowMouseCursor == true
			* for the First Local Player Controller.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static bool IsShowingCursorChecked(const FString& Context, UObject* WorldContext);

			/**
			* Show the mouse cursor. This sets bShowMouseCursor = true for the
			* First Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ShowCursorChecked(const FString& Context, UObject* WorldContext);

			/**
			* Hide the mouse cursor. This sets bShowMouseCursor = false for the 
			* Fist Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void HideCursorChecked(const FString& Context, UObject* WorldContext);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param [out] Position
			*/
			static void GetPositionChecked(const FString& Context, UObject* WorldContext, FIntPoint& Position);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X
			* @param Y
			*/
			static void SetPositionChecked(const FString& Context, UObject* WorldContext, const int32& X, const int32& Y);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void SetCenterOfViewportChecked(const FString& Context, UObject* WorldContext);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void RefreshPositionChecked(const FString& Context, UObject* WorldContext);
		};
	}

	namespace NTouch
	{
		struct CSCORE_API FLibrary final
		{
		public:
			/**
			*
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FingerIndex
			* @param [out] Position
			*/
			static bool GetPositionChecked(const FString& Context, UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& Position);
		};
	}
}