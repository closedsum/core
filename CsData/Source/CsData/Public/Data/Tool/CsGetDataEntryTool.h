// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetDataEntryTool.generated.h"

struct FCsDataEntry_Data;
struct FCsDataEntry_ScriptData;
struct FCsDataEntry_DataTable;

namespace NCsData
{
	namespace NEntry
	{
		namespace NTool
		{
			struct CSDATA_API FImpl
			{
			public:

				void(*Data_PopulateImpl)(FCsDataEntry_Data* /*Entry*/);
				void(*ScriptData_PopulateImpl)(FCsDataEntry_ScriptData* /*Entry*/);
				void(*DataTable_PopulateImpl)(UObject* /*DataTable*/, const FName& /*RowName*/, FCsDataEntry_DataTable* /*Entry*/, const bool& /*AllRows*/);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSDATA_API UCsGetDataEntryTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSDATA_API ICsGetDataEntryTool
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using DataEntryToolType = NCsData::NEntry::NTool::FImpl;
	};

public:

	virtual _::DataEntryToolType* GetDataEntryTool() = 0;
};