// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUILibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUIGetDataRootSet.h"
#include "Data/CsUIDataRootSet.h"

namespace NCsUIDataRootSet
{
	const FCsUIDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* ContextRoot)
	{
		return NCsDataRootSet::FLibrary::GetChecked<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
	}
}