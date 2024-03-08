// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetAssetTool.generated.h"

class UObject;

namespace NCsAsset
{
	namespace NTool
	{
		struct CSCORE_API FImpl
		{
		public:

			const TArray<TWeakObjectPtr<UObject>>&(*GetOpenedAssetsImpl)();

			bool(*IsAssetOpenedImpl)(UObject* /*Asset*/);
		};
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetAssetTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetAssetTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define AssetToolType NCsAsset::NTool::FImpl

	virtual AssetToolType* GetAssetTool() = 0;

#undef AssetToolType
};