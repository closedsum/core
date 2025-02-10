// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsWpPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsWpGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

const FCsWpDataRootSet* FCsWpPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, ContextRoot);
}

using PayloadType = FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload;

void FCsWpPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
	const FCsWpDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

	if (!DataRootSet)
		return;

	using BasePayloadType = CsEnumStructPopulateLibrary::FFromDataTable::FPayload;
	BasePayloadType P;

	P.ContextRoot			= Payload.ContextRoot;
	P.DataTableSoftObject	= DataRootSet->GetDataTableSoftObjectChecked(Context, Payload.DataTableName);
	P.EnumName				= Payload.EnumName;
	P.Create				= Payload.Create;
	P.CreateCustom			= Payload.CreateCustom;
	P.IsValidEnum			= Payload.IsValidEnum;
	P.IsValidEnumByDisplayName = Payload.IsValidEnumByDisplayName;
	P.Log					= Payload.Log;

	CsEnumStructPopulateLibrary::FromDataTable(Context, P);
}