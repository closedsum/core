// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "CsEdTypes_DataTable.h"
#include "CsEdDataTableSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Editor DataTable Settings"))
class CSEDDATATABLE_API UCsEdDataTableSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly)
	TSet<FCsDataTableImportExportInfo> ImportExportInfos;
};