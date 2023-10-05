
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_DeveloperSettings.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

namespace NCsCore
{
	namespace NSettings
	{
		UCsDeveloperSettings* FLibrary::Get() { return GetMutableDefault<UCsDeveloperSettings>(); }

		// Data
		#pragma region

		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSetChecked(const FString& Context)
		{
		#if UE_BUILD_SHIPPING
			return Get()->DataRootSet;
		#else
			UCsDeveloperSettings* Settings = Get();

			checkf(Settings, TEXT("%s: Failed to Get Developer Settings."), *Context);

			return Settings->DataRootSet;
		#endif // #if UE_BUILD_SHIPPING
		}

		const TSoftClassPtr<UObject>& FLibrary::GetDataRootSet()			{ return Get()->DataRootSet; }
		UObject* FLibrary::LoadDataRootSetChecked(const FString& Context)	{ return Get()->LoadDataRootSetChecked(Context); }
		UObject* FLibrary::SafeLoadDataRootSet(const FString& Context)		{ return Get()->SafeLoadDataRootSet(Context); }
		const TArray<FString>& FLibrary::GetIgnoreAssetPaths()				{ return Get()->IgnoreAssetPaths; }

		#pragma endregion Data

		// Input
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_InputActionMap()	{ return Get()->GetSettingsEnum<FECsInputActionMap>(); }
		const FString& FLibrary::GetSettingsEnumPath_InputActionMap()				{ return NCsDeveloperSettings::NCached::Str::InputActionMap; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_GameEvent()		{ return Get()->GetSettingsEnum<FECsGameEvent>(); }
		const FString& FLibrary::GetSettingsEnumPath_GameEvent()					{ return NCsDeveloperSettings::NCached::Str::GameEvent; }

		#pragma endregion Input
		
		// SkeletalMesh
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_StaticMeshActor()	{ return Get()->GetSettingsEnum<FECsStaticMeshActor>(); }
		const FString& FLibrary::GetSettingsEnumPath_StaticMeshActor()				{ return NCsDeveloperSettings::NCached::Str::StaticMeshActor; }
		FECsStaticMeshActor* FLibrary::GetDefault_ECsStaticMeshActor()			{ return &(Get()->Default_ECsStaticMeshActor); }

		#pragma endregion SkeletaMesh

		// SkeletalMesh
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_SkeletalMeshActor()	{ return Get()->GetSettingsEnum<FECsSkeletalMeshActor>(); }
		const FString& FLibrary::GetSettingsEnumPath_SkeletalMeshActor()				{ return NCsDeveloperSettings::NCached::Str::SkeletalMeshActor; }
		FECsSkeletalMeshActor* FLibrary::GetDefault_ECsSkeletalMeshActor()				{ return &(Get()->Default_ECsSkeletalMeshActor); }

		#pragma endregion SkeletaMesh

		// Anim
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::GetVertexAnimNotify_PopulateEnumMapMethod()	{ return Get()->ECsVertexAnimNotify_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_VertexAnimNotify()			{ return Get()->GetSettingsEnum<FECsVertexAnimNotify>(); }
		const FString& FLibrary::GetSettingsEnumPath_VertexAnimNotify()							{ return NCsDeveloperSettings::NCached::Str::VertexAnimNotify; }

		#pragma endregion Anim
	}
}