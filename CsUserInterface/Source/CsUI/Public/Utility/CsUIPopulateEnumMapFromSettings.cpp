// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsUIPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsUIGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

using PayloadType = FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload;

const FCsUIDataRootSet* FCsUIPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
}

void FCsUIPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
	const FCsUIDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

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