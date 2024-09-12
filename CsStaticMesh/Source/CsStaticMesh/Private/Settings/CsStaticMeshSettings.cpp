// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsStaticMeshSettings.h"

// Types
#include "CsMacro_Misc.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsStaticMeshSettings)

// Cached
#pragma region

namespace NCsStaticMeshSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSSTATICMESH_API CS_DEFINE_CACHED_STRING(StaticMeshActor, "UCsStaticMeshSettings::StaticMeshActor");
		}
	}
}

#pragma endregion Cached

UCsStaticMeshSettings::UCsStaticMeshSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_StaticMeshActor()
{
}