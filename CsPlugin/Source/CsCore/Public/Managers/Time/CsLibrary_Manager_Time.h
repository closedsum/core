// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Time/CsTypes_Update.h"
#pragma once

class UObject;

namespace NCsTime
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get the Context (Root) for UCsManager_Time from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Time
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

			/**
			* 
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group
			*/
			static void UpdateTimeAndCoroutineScheduler(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& DeltaTime);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group
			* @param Scale
			*/
			static void SetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& Scale);

			/**
			* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group
			*/
			static void ResetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group);
		};
	}
}