// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPrjPopulateEnumMapFromSettings.h"

// Data
#include "Data/CsPrjGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

const FCsPrjDataRootSet* FCsPrjPopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, ContextRoot);
}

#define PayloadType FCsPrjPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsPrjPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType

	const FCsPrjDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

	if (!DataRootSet)
		return;

	typedef CsEnumStructPopulateLibrary::FFromDataTable::FPayload PayloadType;
	PayloadType P;

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