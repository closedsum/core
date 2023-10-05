// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Fade.generated.h"

// FCsSettings_Manager_Fade
#pragma region

class UCsManager_Fade;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_Fade
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Managers|Fade", meta = (MustImplement = "/Script.CsUI.CsManager_Fade"))
	TSoftClassPtr<UCsManager_Fade> Class;

	FCsSettings_Manager_Fade();

	static const FCsSettings_Manager_Fade& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Fade