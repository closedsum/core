// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsWpLibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsWpGetDataRootSet.h"
#include "Data/CsWpDataRootSet.h"

namespace NCsWeapon
{
	namespace NDataRootSet
	{
		const FCsWpDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* ContextRoot)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, ContextRoot);
		}
	}
}