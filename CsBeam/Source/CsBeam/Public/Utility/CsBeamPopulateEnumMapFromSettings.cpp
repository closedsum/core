// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsBeamPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsBeamGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsBeamDataRootSet* FCsBeamPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsBeamDataRootSet, ICsBeamGetDataRootSet, &ICsBeamGetDataRootSet::GetCsBeamDataRootSet>(Context, ContextRoot);
}