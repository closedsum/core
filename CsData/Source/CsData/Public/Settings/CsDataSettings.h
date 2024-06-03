// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"

// Types
#include "Types/CsTypes_Platform.h"
// Data
#include "Managers/Data/CsSettings_Manager_Data.h"
#include "Data/CsSettings_Data.h"
#include "Data/CsTypes_DataRootSet.h"

#include "CsDataSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsData Settings"))
class CSDATA_API UCsDataSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()


// UObject Interface
#pragma region
public:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion UObject Interface

// Data
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (MustImplement = "/Script/CsData.CsDataRootSet"))
	TSoftClassPtr<UObject> DataRootSet;

	UObject* LoadDataRootSetChecked(const FString& Context);
	UObject* SafeLoadDataRootSet(const FString& Context);

	UPROPERTY(config, EditAnywhere, Category = "Settings|Data")
	FCsSettings_DataRootSet DataRootSets[(uint8)ECsPlatform::ECsPlatform_MAX];

	FORCEINLINE const TSoftClassPtr<UObject>& GetDataRootSet(const ECsPlatform& Platform) const
	{
		return DataRootSets[(uint8)Platform].DataRootSet;
	}

	FORCEINLINE const FDirectoryPath& GetDirectoryToAlwaysCook(const ECsPlatform& Platform) const
	{
		return DataRootSets[(uint8)Platform].DirectoryToAlwaysCook;
	}

	UPROPERTY(config, EditAnywhere, Category = "Settings|Data")
	TArray<FString> IgnoreAssetPaths;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (DisplayName = "Manager Data"))
	FCsSettings_Manager_Data Manager_Data;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data")
	FCsSettings_Data Data;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (DisplayName = "On Editor Startup: Load DataRootSets[Windows]"))
	bool bOnEditorStartup_LoadDataRootSet;

#if WITH_EDITOR
	void PopulateAll(const ECsPlatform& Platform);
#endif // #if WITH_EDITOR

#pragma endregion Data
};