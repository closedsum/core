// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsSePopulateEnumMapFromSettings.h"

// Data
#include "Data/CsSeGetDataRootSet.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

const FCsSeDataRootSet* FCsSePopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, ContextRoot);
}

const FCsSeDataRootSet* FCsSePopulateEnumMapFromSettings::GetDataRootSet(const FString& Context, UObject* ContextRoot, UObject*& OutDataRootSetImpl)
{
	return CsEnumStructPopulateLibrary::GetDataRootSet<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, ContextRoot, OutDataRootSetImpl);
}

#define PayloadType FCsSePopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsSePopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType

	const FCsSeDataRootSet* DataRootSet = GetDataRootSet(Context, Payload.ContextRoot);

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