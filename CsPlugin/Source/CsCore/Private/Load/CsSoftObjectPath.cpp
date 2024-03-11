// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Load/CsSoftObjectPath.h"
#include "CsCore.h"

// FCsTArraySoftObjectPath
#pragma region

#if WITH_EDITOR

void FCsTArraySoftObjectPath::Populate(UObject* O, const FSoftObjectPath& Path, bool bLog /*=true*/)
{
	FCsSoftObjectPath TempPath;
	TempPath.Path = Path;

	FSetElementId Id			= Set.Add(TempPath);
	FCsSoftObjectPath& PathAtId = Set[Id];

	PathAtId.Path = Path;
	int32 RawSize = O->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);

	if (RawSize > 0)
		PathAtId.Size.SetBytes(RawSize);

	if (bLog)
	{
		UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(Path.ToString()), *(PathAtId.Size.ToString()));
	}
}

void FCsTArraySoftObjectPath::Populate(const TSet<FSoftObjectPath>& InSet, bool bLog /*=true*/)
{
	int32 I = 0;

	for (const FSoftObjectPath& Path : InSet)
	{
		// Load Object and get the Resource Size
		UObject* Object = Path.TryLoad();

		int32 Bytes = 0;

		if (Object)
		{
			Bytes = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
		}
		else
		{
			if (bLog)
			{
				UE_LOG(LogCs, Warning, TEXT("--- Failed to load Path: %s @ %s."), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
			}
			continue;
		}

		// Update the Paths
		FCsSoftObjectPath TempPath;
		TempPath.Path = Path;

		// Cumulative
		FSetElementId Id			= Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Set[Id];

		PathAtId.Path = Path;

		if (Bytes > 0)
			PathAtId.Size.SetBytes(Bytes);

		if (bLog)
		{
			UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] %s @ %s."), I, *(PathAtId.Size.ToString()), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
		}
		++I;
	}

	// Update internal structures for fast search / look up
	BuildFromSet();

	if (bLog)
	{
		UE_LOG(LogCs, Warning, TEXT("- Summary: Populated %d Paths [%s]."), Internal.Num(), *(Size.ToString()));
	}
}

#endif // #if WITH_EDITOR

#pragma endregion FCsTArraySoftObjectPath