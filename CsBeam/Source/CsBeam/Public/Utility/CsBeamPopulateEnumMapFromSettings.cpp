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

#define PayloadType FCsBeamPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsBeamPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType

	const FCsBeamDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

	if (!DataRootSet)
		return;

	typedef FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;
	PayloadType P;

	P.ContextRoot			= Payload.ContextRoot;
	//P.DataTableSoftObject	= DataRootSet->GetDataTableSoftObjectChecked(Context, Payload.DataTableName);
	P.EnumName				= Payload.EnumName;
	P.Create				= Payload.Create;
	P.CreateCustom			= Payload.CreateCustom;
	P.IsValidEnum			= Payload.IsValidEnum;
	P.IsValidEnumByDisplayName = Payload.IsValidEnumByDisplayName;
	P.Log					= Payload.Log;

	FCsPopulateEnumMapFromSettings::FromDataTable(Context, P);
}