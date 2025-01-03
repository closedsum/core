// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsDmgPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsDmgGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

const FCsDmgDataRootSet* FCsDmgPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, ContextRoot);
}