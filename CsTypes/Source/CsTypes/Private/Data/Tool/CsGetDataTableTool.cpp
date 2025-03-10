// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Tool/CsGetDataTableTool.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsGetDataTableTool)

namespace NCsDataTable
{
	namespace NTool
	{
		void FImpl::QueueRowNameChange(const UDataTable* DataTable, const FName& CurrentRowName, const FName& NewRowName) 
		{ 
			RowNameChangeType& Change = RowNameChanges.AddDefaulted_GetRef();
			Change.Set(DataTable);
			Change.CurrentRowName = CurrentRowName;
			Change.NewRowName	  = NewRowName;
		}
	}
}

UCsGetDataTableTool::UCsGetDataTableTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}