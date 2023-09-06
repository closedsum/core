// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsWpPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsWpGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

const FCsWpDataRootSet* FCsWpPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, ContextRoot);
}

#define PayloadType FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsWpPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType

	const FCsWpDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

	if (!DataRootSet)
		return;

	typedef FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;
	PayloadType P;

	P.ContextRoot			= Payload.ContextRoot;
	P.DataTableSoftObject	= DataRootSet->GetDataTableSoftObjectChecked(Context, Payload.DataTableName);
	P.EnumName				= Payload.EnumName;
	P.Create				= Payload.Create;
	P.CreateCustom			= Payload.CreateCustom;
	P.IsValidEnum			= Payload.IsValidEnum;
	P.IsValidEnumByDisplayName = Payload.IsValidEnumByDisplayName;
	P.Log					= Payload.Log;

	FCsPopulateEnumMapFromSettings::FromDataTable(Context, P);
}