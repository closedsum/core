// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetDataEntryTool.generated.h"

struct FCsDataEntry_Data;
struct FCsDataEntry_DataTable;

namespace NCsData
{
	namespace NEntry
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

				void(*Data_PopulateImpl)(FCsDataEntry_Data* /*Entry*/);
				void(*DataTable_PopulateImpl)(UObject* /*DataTable*/, const FName& /*RowName*/, FCsDataEntry_DataTable* /*Entry*/, const bool& /*AllRows*/);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetDataEntryTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetDataEntryTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define DataEntryToolType NCsData::NEntry::NTool::FImpl

	virtual DataEntryToolType* GetDataEntryTool() = 0;

#undef DataEntryToolType
};