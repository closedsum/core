// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsAnimLibrary_Asset.h"
#include "CsAnimation.h"

// Library
#include "Library/CsLibrary_Asset.h"

#if WITH_EDITOR

// Level Sequence
#include "../LevelSequence/Public/LevelSequence.h"

#endif // #if WITH_EDITOR

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

UCsAnimLibrary_Asset::UCsAnimLibrary_Asset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Asset Registry
#pragma region

#if WITH_EDITOR

ULevelSequence* UCsAnimLibrary_Asset::CreateLevelSequence(const FString &Name, const FString &PackagePath)
{
	return Cast<ULevelSequence>(UCsLibrary_Asset::CreateAsset(ULevelSequence::StaticClass(), Name, PackagePath));
}

#endif // #if WITH_EDITOR

#pragma endregion Asset Registry