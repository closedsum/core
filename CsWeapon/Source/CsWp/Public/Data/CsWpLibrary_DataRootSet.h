// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsWpDataRootSet.h"

#pragma once

class UObject;

namespace NCsWeapon
{
	namespace NDataRootSet
	{
		/**
		*/
		struct CSWP_API FLibrary final
		{
		public:

			static const FCsWpDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
		};
	}
}