// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsWpPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsWpGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsWpDataRootSet* FCsWpPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, ContextRoot);
}