// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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