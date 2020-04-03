// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Asset_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Asset.h"

// Cache
#pragma region

namespace NCsCommonAssetCached
{
	namespace Str
	{
		const FString bp_data_mapping = TEXT("bp_data_mapping");
	}
}

#pragma endregion // Cache

UCsLibrary_Asset_DEPRECATED::UCsLibrary_Asset_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if WITH_EDITOR

UCsDataMapping* UCsLibrary_Asset_DEPRECATED::GetDataMapping()
{
	return UCsLibrary_Asset::GetBlueprintDefaultObject<UCsDataMapping>(NCsCommonAssetCached::Str::bp_data_mapping, ECsStringCompare::Equals, UCsDataMapping::StaticClass());
}

#endif // #if WITH_EDITOR