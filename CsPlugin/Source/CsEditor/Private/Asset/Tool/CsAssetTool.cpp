// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Asset/Tool/CsAssetTool.h"

// Library
#include "Library/CsLibrary_Blueprint.h"
// Engine
#include "CsEdEngine.h"

namespace NCsAsset
{
	const TArray<TWeakObjectPtr<UObject>>& FTool::GetOpenedAssets()
	{
		return Cast<UCsEdEngine>(GEngine)->GetOpenedAssets();
	}

	bool FTool::IsAssetOpened(UObject* Asset)
	{
		if (!IsValid(Asset))
			return false;

		for (const TWeakObjectPtr<UObject>& O : GetOpenedAssets())
		{
			UObject* A = O.IsValid() ? O.Get() : nullptr;

			if (Asset == A)
				return true;
		}
		return false;
	}

	bool FTool::IsAssetWithClassDefaultOpened(UObject* DefaultObject)
	{
		if (!IsValid(DefaultObject))
			return false;

		for (const TWeakObjectPtr<UObject>& O : GetOpenedAssets())
		{
			UObject* A = O.IsValid() ? O.Get() : nullptr;

			if (DefaultObject == CsBlueprintLibrary::GetSafeClassDefaultObject(A))
				return true;
		}
		return false;
	}
}