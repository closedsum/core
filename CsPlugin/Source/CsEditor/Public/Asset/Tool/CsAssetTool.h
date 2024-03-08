// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;

namespace NCsAsset
{
	struct CSEDITOR_API FTool
	{
	public:

		static const TArray<TWeakObjectPtr<UObject>>& GetOpenedAssets();

		static bool IsAssetOpened(UObject* Asset);
	};
}