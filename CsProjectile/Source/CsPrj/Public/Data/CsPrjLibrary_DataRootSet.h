// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjDataRootSet.h"

#pragma once

class UObject;

namespace NCsProjectile
{
	namespace NDataRootSet
	{
		/**
		*/
		struct CSPRJ_API FLibrary final
		{
		public:

			static const FCsPrjDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
		};
	}
}