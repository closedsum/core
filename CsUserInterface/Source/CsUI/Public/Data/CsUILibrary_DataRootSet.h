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

		static const FCsUIDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
	};
}