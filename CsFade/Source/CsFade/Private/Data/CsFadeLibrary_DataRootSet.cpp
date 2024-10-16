// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsFadeLibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Utility
#include "Utility/CsFadeLog.h"
// Data
#include "Data/CsFadeGetDataRootSet.h"
#include "Data/CsFadeDataRootSet.h"

namespace NCsFade
{
	namespace NDataRootSet
	{
		const FCsFadeDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
		{
			return CsDataRootSetLibrary::GetSafe<FCsFadeDataRootSet, ICsFadeGetDataRootSet, &ICsFadeGetDataRootSet::GetCsFadeDataRootSet>(Context, WorldContext, &NCsFade::FLog::Warning);
		}

		const FCsFadeDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			return CsDataRootSetLibrary::GetChecked<FCsFadeDataRootSet, ICsFadeGetDataRootSet, &ICsFadeGetDataRootSet::GetCsFadeDataRootSet>(Context, GameInstance);
		}

		const FCsFadeDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			return CsDataRootSetLibrary::GetChecked<FCsFadeDataRootSet, ICsFadeGetDataRootSet, &ICsFadeGetDataRootSet::GetCsFadeDataRootSet>(Context, WorldContext);
		}

		UClass* FLibrary::GetFadeWidgetClassChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext).GetFadeWidgetClassChecked(Context);
		}
	}
}