// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UDataTable;

namespace NCsDataTable
{
	namespace NProperty
	{
		namespace NRowName
		{
			struct CSCORE_API FChange
			{
			public:

				TWeakObjectPtr<UDataTable> DataTable;

				FName CurrentRowName;

				FName NewRowName;

				FChange() :
					DataTable(nullptr),
					CurrentRowName(NAME_None),
					NewRowName(NAME_None)
				{
				}

				UDataTable* Get() const;

				void Set(const UDataTable* InDataTable);

				bool IsValid() const;

				bool Execute(UDataTable* InDataTable) const;
			};
		}
	}
}