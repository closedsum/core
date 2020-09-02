// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsUIPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsUIGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsUIDataRootSet* FCsUIPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
}