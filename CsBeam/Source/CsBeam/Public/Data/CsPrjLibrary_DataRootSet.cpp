// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjLibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjGetDataRootSet.h"
#include "Data/CsPrjDataRootSet.h"

namespace NCsProjectile
{
	namespace NDataRootSet
	{
		const FCsPrjDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* ContextRoot)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, ContextRoot);
		}
	}
}