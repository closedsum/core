// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Tool/CsGetDataTableTool.h"
#include "CsCore.h"

namespace NCsDataTable
{
	namespace NTool
	{
		#define RowNameChangeType NCsDataTable::NProperty::NRowName::FChange

		void FImpl::QueueRowNameChange(const UDataTable* DataTable, const FName& CurrentRowName, const FName& NewRowName) 
		{ 
			RowNameChangeType& Change = RowNameChanges.AddDefaulted_GetRef();
			Change.Set(DataTable);
			Change.CurrentRowName = CurrentRowName;
			Change.NewRowName	  = NewRowName;
		}

		#undef RowNameChangeType
	}
}

UCsGetDataTableTool::UCsGetDataTableTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}