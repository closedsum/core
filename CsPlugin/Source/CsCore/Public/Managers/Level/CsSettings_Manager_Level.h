// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Level.generated.h"

// FCsSettings_Manager_Level
#pragma region

class UCsManager_Level;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Level
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Level", meta = (MustImplement = "/Script.CsCore.CsManager_Level"))
	TSoftClassPtr<UCsManager_Level> Class;

	FCsSettings_Manager_Level();

	static const FCsSettings_Manager_Level& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Level