// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjLibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjGetDataRootSet.h"
#include "Data/CsPrjDataRootSet.h"

const FCsPrjDataRootSet& FCsPrjLibrary_DataRootSet::GetChecked(const FString& Context, UObject* ContextRoot)
{
	return FCsLibrary_DataRootSet::GetChecked<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, ContextRoot);
}