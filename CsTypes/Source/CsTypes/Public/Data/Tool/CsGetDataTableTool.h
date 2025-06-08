// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSTYPES_API FImpl
		{
		public:

			using RowNameChangeType = NCsDataTable::NProperty::NRowName::FChange;

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
							RowNameChanges.RemoveAt(I, 1, EAllowShrinking::No);
							continue;
						}

						if (Change.Execute(DataTable))
						{
							RowNameChanges.RemoveAt(I, 1, EAllowShrinking::No);
							continue;
						}
					}
				}
			}
		};
	}
}

UINTERFACE(Blueprintable)
class CSTYPES_API UCsGetDataTableTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTYPES_API ICsGetDataTableTool
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using DataTableToolType = NCsDataTable::NTool::FImpl;
	};

public:

	virtual _::DataTableToolType* GetDataTableTool() = 0;
};