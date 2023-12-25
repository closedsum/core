// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"

#include "CsUserSettings.generated.h"

UCLASS(config = EditorPerProjectUserSettings)
class CSCORE_API UCsUserSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion UObject Interface

// Editor
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "Editor UI: Application Scale", UIMin = "1.0", ClampMin = "1.0"))
	float EditorUI_ApplicationScale;

#if WITH_EDITOR

	void ApplyEditorUI_ApplicationScale();

#endif // #if WITH_EDITOR

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "Garbage Collection Interval", UIMin = "1.0", ClampMin = "1.0"))
	float GCInterval;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "Force Garbage Collecton on End PIE"))
	bool bForceGCOnEndPIE;

#pragma endregion Editor

// Enum
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "On Save DataTable: Enum Struct Layout Resolve Changes"))
	bool bOnSave_DataTable_EnumStructLayoutResolveChanges;

#pragma endregion Enum

// Data
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "On Save Data: Populate Paths"))
	bool bOnSave_Data_PopulatePaths;
	
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Editor", meta = (DisplayName = "On Save DataTable: Populate Paths"))
	bool bOnSave_DataTable_PopulatePaths;

#pragma endregion Data
};