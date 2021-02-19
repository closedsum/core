// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUIDataRootSet.h"

#pragma once

class UObject;

namespace NCsUIDataRootSet
{
	/**
	*/
	class CSUI_API FLibrary
	{
	public:

		/**
			* Get the Context (Root) for getting FCsUIDataRootSet, which resides on
			* UCsManager_Data, from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Data
			*/
		static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);

		/**
		*/
		static const FCsUIDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
	};
}