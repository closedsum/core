// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Fade/CsTypes_Fade.h"

class UObject;

namespace NCsFade
{
	namespace NManager
	{
		struct CSUI_API FLibrary
		{
		public:

			/**
			* Get the Context (Root) for UCsManager_Fade from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Fade
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

			#define ParamsType NCsFade::FParams
			
			/**
			*
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void CreateFadeWidget(const FString& Context, UObject* WorldContext);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Params
			*/
			static void FadeChecked(const FString& Context, UObject* WorldContext, const ParamsType& Params);
			
			#undef ParamsType

			/**
			* 
			* 
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void StopFadeChecked(const FString& Context, UObject* WorldContext);

			/**
			*
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ClearFadeChecked(const FString& Context, UObject* WorldContext);
		};
	}
}