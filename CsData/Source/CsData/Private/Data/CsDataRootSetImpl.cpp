// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsDataRootSetImpl.h"

// Types
#include "Data/CsTypes_DataEntry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsDataRootSetImpl)

UCsDataRootSetImpl::UCsDataRootSetImpl(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Editor
#pragma region

#if WITH_EDITOR

void UCsDataRootSetImpl::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// DataTables
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataRootSet, DataTables))
	{
		if (Core_DataRootSet.DataTables)
		{
			if (FCsDataEntry_DataTable::StaticStruct() != Core_DataRootSet.DataTables->GetRowStruct())
			{
				Core_DataRootSet.DataTables = nullptr;
			}
		}
	}
	// Payloads

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion Editor