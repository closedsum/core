// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUILibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Managers/Data/CsLibrary_Manager_Data.h"
// Data
#include "Data/CsUIGetDataRootSet.h"
#include "Data/CsUIDataRootSet.h"

namespace NCsUIDataRootSet
{
	UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetContextRootChecked(Context, WorldContext);
	}

	const FCsUIDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* ContextRoot)
	{
		return NCsDataRootSet::FLibrary::GetChecked<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
	}
}