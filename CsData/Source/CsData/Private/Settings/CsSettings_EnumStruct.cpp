// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsSettings_EnumStruct.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// DataTable
#include "Data/Tool/CsGetDataTableTool.h"

#if WITH_EDITOR
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_EnumStruct)

namespace NCsSettingsEnumStructPopulateByDataTable
{
	namespace NCached
	{
		namespace Str
		{
			const FString Default__ = TEXT("Default__");
			const FString BP_Data_ = TEXT("BP_Data_");
			const FString BP_ScriptData_ = TEXT("BP_ScriptData_");
			const FString _C = TEXT("_C");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsSettings_EnumStruct_PopulateByDataTable, OnDataTableChanged);
		}
	}
}

#define USING_NS_CACHED using namespace NCsSettingsEnumStructPopulateByDataTable::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsSettingsEnumStructPopulateByDataTable::NCached; \
	const FString& Context = Str::__FunctionName

void FCsSettings_EnumStruct_PopulateByDataTable::OnDataTableChanged(const UDataTable* InDataTable, const FName& InRowName, FString& OutName, FString& OutDisplayName, const FString& AssetName) const
{
	SET_CONTEXT(OnDataTableChanged);

#if WITH_EDITOR
	FString NewRowName;

	if (!AssetName.IsEmpty())
	{
		NewRowName = AssetName;

		if (bRemoveFromStart_Default)
			NewRowName.RemoveFromStart(Str::Default__);
		if (bRemoveFromStart_BP_Data)
			NewRowName.RemoveFromStart(Str::BP_Data_);
		if (bRemoveFromStart_BP_ScriptData)
			NewRowName.RemoveFromStart(Str::BP_ScriptData_);

		for (const FString& Prefix : PrefixesToRemoveFromStart)
		{
			NewRowName.RemoveFromStart(Prefix);
		}

		NewRowName.RemoveFromEnd(Str::_C);

		for (const FString& Suffix : SuffixesToRemoveFromStart)
		{
			NewRowName.RemoveFromEnd(Suffix);
		}
	}

	if (bPopulateNamesByData)
	{
		if (!AssetName.IsEmpty())
		{
			// Check to Queue a DataTable Property Change (RowName)
			const FString CurrentRowName = InRowName.ToString();

			if (NewRowName.Compare(CurrentRowName, ESearchCase::IgnoreCase) != 0)
			{
				using DataTableToolType = NCsDataTable::NTool::FImpl;

				ICsGetDataTableTool* GetDataTableTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetDataTableTool);
				DataTableToolType* DataTableTool	  = GetDataTableTool->GetDataTableTool();

				const FName NewRowNameAsName = FName(*NewRowName);

				DataTableTool->QueueRowNameChange(InDataTable, InRowName, NewRowNameAsName);
			}

			OutName		   = NewRowName;
			OutDisplayName = NewRowName;
			return;
		}
	}

	if (InRowName == NAME_None)
	{
		if (!AssetName.IsEmpty())
		{
			if (OutName.IsEmpty())
			{
				OutName = NewRowName;
			}

			if (OutDisplayName.IsEmpty())
			{
				OutDisplayName = NewRowName;
			}
		}
	}
	else
	{
		if (OutName.IsEmpty())
		{
			OutName = InRowName.ToString();
		}

		if (OutDisplayName.IsEmpty())
		{
			OutDisplayName = OutName;
		}
	}
#endif // #if WITH_EDITOR
}

void FCsSettings_EnumStruct_PopulateByDataTable::OnDataTableChanged(const UDataTable* InDataTable, const FName& InRowName, FName& OutName, const FString& AssetName) const
{
	SET_CONTEXT(OnDataTableChanged);

#if WITH_EDITOR
	FString NewRowName;

	if (!AssetName.IsEmpty())
	{
		NewRowName = AssetName;

		if (bRemoveFromStart_Default)
			NewRowName.RemoveFromStart(Str::Default__);
		if (bRemoveFromStart_BP_Data)
			NewRowName.RemoveFromStart(Str::BP_Data_);
		if (bRemoveFromStart_BP_ScriptData)
			NewRowName.RemoveFromStart(Str::BP_ScriptData_);

		for (const FString& Prefix : PrefixesToRemoveFromStart)
		{
			NewRowName.RemoveFromStart(Prefix);
		}

		NewRowName.RemoveFromEnd(Str::_C);

		for (const FString& Suffix : SuffixesToRemoveFromStart)
		{
			NewRowName.RemoveFromEnd(Suffix);
		}
	}

	if (bPopulateNamesByData)
	{
		if (!AssetName.IsEmpty())
		{
			// Check to Queue a DataTable Property Change (RowName)
			const FString CurrentRowName = InRowName.ToString();

			if (NewRowName.Compare(CurrentRowName, ESearchCase::IgnoreCase) != 0)
			{
				using DataTableToolType = NCsDataTable::NTool::FImpl;

				ICsGetDataTableTool* GetDataTableTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetDataTableTool);
				DataTableToolType* DataTableTool	  = GetDataTableTool->GetDataTableTool();

				const FName NewRowNameAsName = FName(*NewRowName);

				DataTableTool->QueueRowNameChange(InDataTable, InRowName, NewRowNameAsName);
			}

			OutName = FName(*NewRowName);
			return;
		}
	}

	if (InRowName == NAME_None)
	{
		if (!AssetName.IsEmpty())
		{
			if (OutName == NAME_None)
			{
				OutName = FName(*NewRowName);
			}
		}
	}
	else
	{
		if (OutName == NAME_None)
		{
			OutName = InRowName;
		}
	}
#endif // #if WITH_EDITOR
}

#undef USING_NS_CACHED
#undef SET_CONTEXT