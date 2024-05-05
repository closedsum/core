// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_PlayerProfile.generated.h"

// FCsSettings_Manager_PlayerProfile
#pragma region

class UCsManager_PlayerProfile;
class UClass;

USTRUCT(BlueprintType)
struct CSPLATFORMSERVICES_API FCsSettings_Manager_PlayerProfile
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPlatformServices|Managers|Player Profile")
	TSoftClassPtr<UCsManager_PlayerProfile> Class;

	FCsSettings_Manager_PlayerProfile();

	static const FCsSettings_Manager_PlayerProfile& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_PlayerProfile