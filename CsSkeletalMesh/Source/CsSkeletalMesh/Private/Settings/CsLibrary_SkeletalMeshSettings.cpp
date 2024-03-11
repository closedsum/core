
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_SkeletalMeshSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsSkeletalMeshSettings.h"
// Interface
#include "SourceControl/Tool/CsGetSourceControlTool.h"

namespace NCsSkeletalMesh
{
	namespace NSettings
	{
		UCsSkeletalMeshSettings* FLibrary::Get() { return GetMutableDefault<UCsSkeletalMeshSettings>(); }

		#define USING_NS_CACHED using namespace NCsSkeletalMesh::NSettings::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsSkeletalMesh::NSettings::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// SkeletalMesh
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_SkeletalMeshActor()	{ return Get()->GetSettingsEnum<FECsSkeletalMeshActor>(); }
		const FString& FLibrary::GetSettingsEnumPath_SkeletalMeshActor()				{ return NCsSkeletalMeshSettings::NCached::Str::SkeletalMeshActor; }
		FECsSkeletalMeshActor* FLibrary::GetDefault_ECsSkeletalMeshActor()				{ return &(Get()->Default_ECsSkeletalMeshActor); }

		#pragma endregion SkeletaMesh

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}