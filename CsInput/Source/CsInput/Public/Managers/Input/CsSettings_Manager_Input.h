// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Input/CsTypes_Input.h"

#include "CsSettings_Manager_Input.generated.h"

// FCsSettings_Manager_Input
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsSettings_Manager_Input
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Managers|Input", NoClear, meta = (MustImplement = "/Script/CsInput.CsManager_Input"))
	TSoftClassPtr<UObject> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Managers|Input")
	int32 InputPoolSize;
	 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Managers|Input")
	TArray<int32> RemappedGamepadControllerIds;

	FCsSettings_Manager_Input();

	static const FCsSettings_Manager_Input& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Input

// FCsSettings_Manager_Input_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsSettings_Manager_Input_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Input_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Input_UnitTest