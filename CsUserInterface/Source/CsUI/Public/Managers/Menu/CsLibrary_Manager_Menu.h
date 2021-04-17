// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once

class UObject;

namespace NCsMenu
{
	namespace NManager
	{
		struct CSUI_API FLibrary
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Menu from a ContextObject.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Menu
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR
		};
	}
}