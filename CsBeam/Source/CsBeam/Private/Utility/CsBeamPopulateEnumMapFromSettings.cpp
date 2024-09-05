// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsBeamPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsBeamGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

const FCsBeamDataRootSet* FCsBeamPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsBeamDataRootSet, ICsBeamGetDataRootSet, &ICsBeamGetDataRootSet::GetCsBeamDataRootSet>(Context, ContextRoot);
}

#define PayloadType FCsBeamPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsBeamPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType

	const FCsBeamDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

	if (!DataRootSet)
		return;

	typedef CsEnumStructPopulateLibrary::FFromDataTable::FPayload PayloadType;
	PayloadType P;

	P.ContextRoot			= Payload.ContextRoot;
	//P.DataTableSoftObject	= DataRootSet->GetDataTableSoftObjectChecked(Context, Payload.DataTableName);
	P.EnumName				= Payload.EnumName;
	P.Create				= Payload.Create;
	P.CreateCustom			= Payload.CreateCustom;
	P.IsValidEnum			= Payload.IsValidEnum;
	P.IsValidEnumByDisplayName = Payload.IsValidEnumByDisplayName;
	P.Log					= Payload.Log;

	CsEnumStructPopulateLibrary::FromDataTable(Context, P);
}