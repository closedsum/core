// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
#include "Managers/SkeletalMesh/CsSettings_Manager_SkeletalMeshActor.h"

#include "CsSkeletalMeshSettings.generated.h"

// Cached
#pragma region

namespace NCsSkeletalMeshSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSSKELETALMESH_API const FString SkeletalMeshActor;
		}
	}
}

#pragma endregion Cached

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Skeletal Mesh Settings"))
class CSSKELETALMESH_API UCsSkeletalMeshSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsSkeletalMeshActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsSkeletalMeshActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsSkeletalMeshActor>() const { return ECsSkeletalMeshActor; }
	template<>
	const FString& GetSettingsEnumPath<FECsSkeletalMeshActor>() const { return NCsSkeletalMeshSettings::NCached::Str::SkeletalMeshActor; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "Default Value: ECsSkeletalMeshActor"))
	FECsSkeletalMeshActor Default_ECsSkeletalMeshActor;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "Manager Skeletal Mesh Actor"))
	FCsSettings_Manager_SkeletalMeshActor Manager_SkeletalMeshActor;
};