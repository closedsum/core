// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsDmgPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsDmgGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsDmgDataRootSet* FCsDmgPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, ContextRoot);
}