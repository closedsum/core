
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_StaticMeshSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsStaticMeshSettings.h"

namespace NCsStaticMesh
{
	namespace NSettings
	{
		UCsStaticMeshSettings* FLibrary::Get() { return GetMutableDefault<UCsStaticMeshSettings>(); }

		#define USING_NS_CACHED using namespace NCsStaticMesh::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsStaticMesh::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// StaticMesh
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_StaticMeshActor()	{ return Get()->GetSettingsEnum<FECsStaticMeshActor>(); }
		const FString& FLibrary::GetSettingsEnumPath_StaticMeshActor()				{ return NCsStaticMeshSettings::NCached::Str::StaticMeshActor; }
		FECsStaticMeshActor* FLibrary::GetDefault_ECsStaticMeshActor()				{ return &(Get()->Default_ECsStaticMeshActor); }

		#pragma endregion SkeletaMesh

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}