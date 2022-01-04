// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsSePopulateEnumMapFromSettings.h"

// Data
#include "Data/CsSeGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsSeDataRootSet* FCsSePopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, ContextRoot);
}

const FCsSeDataRootSet* FCsSePopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot, UObject*& OutDataRootSetImpl)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, ContextRoot, OutDataRootSetImpl);
}