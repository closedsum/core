// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUILibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUIGetDataRootSet.h"
#include "Data/CsUIDataRootSet.h"

const FCsUIDataRootSet& FCsUILibrary_DataRootSet::GetChecked(const FString& Context, UObject* ContextRoot)
{
	return FCsLibrary_DataRootSet::GetChecked<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
}