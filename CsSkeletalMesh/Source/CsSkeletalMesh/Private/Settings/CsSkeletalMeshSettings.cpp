// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsSkeletalMeshSettings.h"

// Cached
#pragma region

namespace NCsSkeletalMeshSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSSKELETALMESH_API CS_DEFINE_CACHED_STRING(SkeletalMeshActor, "UCsSkeletalMeshSettings::SkeletalMeshActor");
		}
	}
}

#pragma endregion Cached

UCsSkeletalMeshSettings::UCsSkeletalMeshSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_SkeletalMeshActor()
{
}