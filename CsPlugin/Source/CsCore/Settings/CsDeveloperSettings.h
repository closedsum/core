// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/CsTypes_Load.h"
#include "CsDeveloperSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Custom Settings"))
class CSCORE_API UCsDeveloperSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	FCsUserDefinedEnum InputAction;

#pragma endregion Enum

// Load
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "CsCore|Load")
	FCsDataTable Datas;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "CsCore|Load")
	FCsDataTable DataTables;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "CsCore|Load")
	FCsDataTable Payloads;

#pragma endregion Load

	// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor
};