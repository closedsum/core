// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsBeamDataRootSet.h"

#pragma once

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