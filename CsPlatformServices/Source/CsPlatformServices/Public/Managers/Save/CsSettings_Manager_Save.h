// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Save.generated.h"

// FCsSettings_Manager_Save
#pragma region

class UCsManager_Save;
class UClass;

USTRUCT(BlueprintType)
struct CSPLATFORMSERVICES_API FCsSettings_Manager_Save
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPlatformServices|Managers|Save")
	TSoftClassPtr<UCsManager_Save> Class;

	FCsSettings_Manager_Save();

	static const FCsSettings_Manager_Save& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Save