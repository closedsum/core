// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Settings/CsTypes_Settings_Enum.h"

class UCsDeveloperSettings;
class UObject;

struct FECsStaticMeshActor;
struct FECsSkeletalMeshActor;

namespace NCsCore
{
	namespace NSettings
	{
		/**
		*/
		class CSCORE_API FLibrary
		{
		public:
			
			static UCsDeveloperSettings* Get();
			
		// Data
		#pragma region
		public:
			
			static const TSoftClassPtr<UObject>& GetDataRootSetChecked(const FString& Context);
			static const TSoftClassPtr<UObject>& GetDataRootSet();

			static UObject* LoadDataRootSetChecked(const FString& Context);
			static UObject* SafeLoadDataRootSet(const FString& Context);

			static const TArray<FString>& GetIgnoreAssetPaths();

		#pragma endregion Data

		// Input
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_InputActionMap();
			static const FString& GetSettingsEnumPath_InputActionMap();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_GameEvent();
			static const FString& GetSettingsEnumPath_GameEvent();

		#pragma endregion Input

		// StaticMesh
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_StaticMeshActor();
			static const FString& GetSettingsEnumPath_StaticMeshActor();
			static FECsStaticMeshActor* GetDefault_ECsStaticMeshActor();

		#pragma endregion StaticMesh

		// SkeletalMesh
		#pragma region
		public:

			static const TArray<FCsSettings_Enum>& GetSettingsEnum_SkeletalMeshActor();
			static const FString& GetSettingsEnumPath_SkeletalMeshActor();
			static FECsSkeletalMeshActor* GetDefault_ECsSkeletalMeshActor();

		#pragma endregion SkeletaMesh

		// Anim
		#pragma region
		public:

			static const ECsPopulateEnumMapMethod& GetVertexAnimNotify_PopulateEnumMapMethod();
			static const TArray<FCsSettings_Enum>& GetSettingsEnum_VertexAnimNotify();
			static const FString& GetSettingsEnumPath_VertexAnimNotify();

		#pragma endregion Anim
		};
	}
}