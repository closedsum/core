// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Internal = TEXT("_Internal");
		CSCORE_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSCORE_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSCORE_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSCORE_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSCORE_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSCORE_API const FString _C = TEXT("_C");
	}
}

// AssetType
EMCsAssetType* EMCsAssetType::Instance;

EMCsAssetType& EMCsAssetType::Get()
{
	if (!Instance)
		Instance = new EMCsAssetType();
	return *Instance;
}