// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Asset/Tool/CsAssetTool.h"

// Engine
#include "CsEdEngine.h"

namespace NCsAsset
{
	const TArray<UObject*>& FTool::GetOpenedAssets()
	{
		return Cast<UCsEdEngine>(GEngine)->GetOpenedAssets();
	}

	bool FTool::IsAssetOpened(UObject* Asset)
	{
		for (UObject* O : GetOpenedAssets())
		{
			if (Asset == O)
				return true;
		}
		return false;
	}
}