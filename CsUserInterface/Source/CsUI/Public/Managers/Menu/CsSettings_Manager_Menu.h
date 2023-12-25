// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Menu.generated.h"

// FCsSettings_Manager_Menu
#pragma region

class UCsManager_Menu;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_Menu
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Managers|Menu")
	TSoftClassPtr<UCsManager_Menu> Class;

	FCsSettings_Manager_Menu();

	static const FCsSettings_Manager_Menu& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Menu