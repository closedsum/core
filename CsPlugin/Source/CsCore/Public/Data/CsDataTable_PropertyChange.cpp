// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsDataTable_PropertyChange.h"

// DataTable
#include "Engine/DataTable.h"

namespace NCsDataTable
{
	namespace NProperty
	{
		namespace NRowName
		{
			UDataTable* FChange::Get() const
			{
				return DataTable.IsValid() ? DataTable.Get() : nullptr;
			}

			void FChange::Set(const UDataTable* InDataTable)
			{
				DataTable = const_cast<UDataTable*>(InDataTable);
			}

			bool FChange::IsValid() const
			{
				UDataTable* DT = Get();

				if (!DT)
					return false;
				if (CurrentRowName == NAME_None)
					return false;
				if (NewRowName == NAME_None)
					return false;
				if (!DT->FindRowUnchecked(CurrentRowName))
					return false;
				if (DT->FindRowUnchecked(NewRowName))
					return false;
				return true;
			}

			bool FChange::Execute(UDataTable* InDataTable) const
			{
				if (Get() == InDataTable)
				{
					// Duplicate the contents of Current Row
					const UScriptStruct* RowStruct  = InDataTable->GetRowStruct();
					UScriptStruct& EmptyUsingStruct = *(const_cast<UScriptStruct*>(RowStruct));

					uint8* CurrentRowData = InDataTable->FindRowUnchecked(CurrentRowName);
					uint8* NewRawRowData = (uint8*)FMemory::Malloc(EmptyUsingStruct.GetStructureSize());
	
					EmptyUsingStruct.InitializeStruct(NewRawRowData);
					EmptyUsingStruct.CopyScriptStruct(NewRawRowData, CurrentRowData);

					// Remove Current Row
					InDataTable->RemoveRow(CurrentRowName);

					// Add NewRowName
					FTableRowBase* RowData = reinterpret_cast<FTableRowBase*>(NewRawRowData);

					InDataTable->AddRow(NewRowName, *RowData);
					return true;
				}
				return false;
			}
		}
	}
}