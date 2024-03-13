// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsBeamLibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsBeamGetDataRootSet.h"
#include "Data/CsBeamDataRootSet.h"

namespace NCsBeam
{
	namespace NDataRootSet
	{
		const FCsBeamDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* ContextRoot)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsBeamDataRootSet, ICsBeamGetDataRootSet, &ICsBeamGetDataRootSet::GetCsBeamDataRootSet>(Context, ContextRoot);
		}
	}
}