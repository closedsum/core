// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "Managers/StaticMesh/CsSettings_Manager_StaticMeshActor.h"
#include "Managers/StaticMesh/Instanced/CsSettings_Manager_InstancedStaticMeshComponent.h"

#include "CsStaticMeshSettings.generated.h"

// Cached
#pragma region

namespace NCsStaticMeshSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSSTATICMESH_API const FString StaticMeshActor;
		}
	}
}

#pragma endregion Cached

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Static Mesh Settings"))
class CSSTATICMESH_API UCsStaticMeshSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

// StaticMesh
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "ECsStaticMeshActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsStaticMeshActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "ECsStaticMeshActor", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsStaticMeshActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsStaticMeshActor>() const { return ECsStaticMeshActor; }
	template<>
	const FString& GetSettingsEnumPath<FECsStaticMeshActor>() const { return NCsStaticMeshSettings::NCached::Str::StaticMeshActor; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Default Value: ECsStaticMeshActor"))
	FECsStaticMeshActor Default_ECsStaticMeshActor;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Manager StaticMeshActor"))
	FCsSettings_Manager_StaticMeshActor Manager_StaticMeshActor;

	// Unit Test
#pragma region

#pragma endregion Unit Test

	// Instanced
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Instanced|Component", meta = (DisplayName = "Manager InstancedStaticMeshComponent"))
	FCsSettings_Manager_InstancedStaticMeshComponent Manager_InstancedStaticMeshComponent;

#pragma endregion Instanced

#pragma endregion StaticMesh

};