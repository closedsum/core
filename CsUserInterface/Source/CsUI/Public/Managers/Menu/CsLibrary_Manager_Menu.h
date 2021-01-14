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

			/**
			* Get the Context (Root) for UCsManager_Menu from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Menu
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		};
	}
}