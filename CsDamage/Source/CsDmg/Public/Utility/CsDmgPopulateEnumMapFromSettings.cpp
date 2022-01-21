// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsDmgPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsDmgGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsDmgDataRootSet* FCsDmgPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, ContextRoot);
}