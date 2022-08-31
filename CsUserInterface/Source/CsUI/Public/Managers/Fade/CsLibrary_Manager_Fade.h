// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Fade/CsTypes_Fade.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_Fade;

namespace NCsFade
{
	namespace NManager
	{
		struct CSUI_API FLibrary
		{
		// ContextRoot
		#pragma region
		public:
		
		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Fade from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Fade
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Fade from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Fade
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void (*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void (*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Fade from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Fade
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Fade from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Fade.
			*/
			static UCsManager_Fade* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Fade from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Fade.
			*/
			static UCsManager_Fade* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Fade from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Fade.
			*/
			static UCsManager_Fade* GetSafe(const UObject* ContextObject);

		#pragma endregion Get

		public:

		#define ParamsType NCsFade::FParams
			
			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			*/
			static void CreateFadeWidget(const FString& Context, const UObject* ContextObject);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Params
			*/
			static void FadeChecked(const FString& Context, const UObject* ContextObject, const ParamsType& Params);
			
			/**
			*
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Params
			*/
			static bool SafeFade(const UObject* ContextObject, const ParamsType& Params);

		#undef ParamsType

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			*/
			static void StopFadeChecked(const FString& Context, const UObject* ContextObject);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			*/
			static void ClearFadeChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely fade the screen from Clear to Black over Time.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Time
			* @param Log			(optional)
			* return
			*/
			static bool SafeFadeClearToBlack(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely fade the screen from Black to Clear over Time.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Time
			* @param Log			(optional)
			* return
			*/
			static bool SafeFadeBlackToClear(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}
}