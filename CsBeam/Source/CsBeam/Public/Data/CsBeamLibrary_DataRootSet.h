// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/CsBeamDataRootSet.h"

class UObject;

namespace NCsBeam
{
	namespace NDataRootSet
	{
		/**
		*/
		struct CSBEAM_API FLibrary final
		{
		public:

			static const FCsBeamDataRootSet& GetChecked(const FString& Context, UObject* ContextRoot);
		};
	}
}