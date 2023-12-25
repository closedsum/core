// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// DataTable
#include "Data/CsDataTable_PropertyChange.h"

#include "CsGetDataTableTool.generated.h"

class UDataTable;

namespace NCsDataTable
{
	namespace NTool
	{
		struct CSCORE_API FImpl
		{
		public:

		#define RowNameChangeType NCsDataTable::NProperty::NRowName::FChange

			TArray<RowNameChangeType> RowNameChanges;

			FImpl() :
				RowNameChanges()
			{
			}

			void QueueRowNameChange(const RowNameChangeType& Change) { RowNameChanges.Add(Change); }
			void QueueRowNameChange(const UDataTable* DataTable, const FName& CurrentRowName, const FName& NewRowName);

			void ProcessChange(UDataTable* DataTable)
			{
				// RowName
				{
					int32 Count = RowNameChanges.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						const RowNameChangeType& Change = RowNameChanges[I];

						if (!Change.IsValid())
						{
							RowNameChanges.RemoveAt(I, 1, false);
							continue;
						}

						if (Change.Execute(DataTable))
						{
							RowNameChanges.RemoveAt(I, 1, false);
							continue;
						}
					}
				}
			}

		#undef RowNameChangeType
		};
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetDataTableTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetDataTableTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define DataTableToolType NCsDataTable::NTool::FImpl

	virtual DataTableToolType* GetDataTableTool() = 0;

#undef DataTableToolType
};