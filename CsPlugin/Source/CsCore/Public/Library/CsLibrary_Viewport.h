// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
class FSceneViewport;

namespace NCsViewport
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
		static bool CanProjectWorldToScreenChecked(const FString& Context, UObject* WorldContext);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*/
		static FSceneViewport* GetLocalPlayerViewportChecked(const FString& Context, UObject* WorldContext);
	};
}