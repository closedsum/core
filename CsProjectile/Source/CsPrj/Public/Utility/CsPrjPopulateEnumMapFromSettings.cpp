// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPrjPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsPrjGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsPrjDataRootSet* FCsPrjPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, ContextRoot);
}