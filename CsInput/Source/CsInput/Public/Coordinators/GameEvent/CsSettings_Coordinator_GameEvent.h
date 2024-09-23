// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Coordinator_GameEvent.generated.h"

// FCsSettings_Coordinator_GameEvent
#pragma region

class UCsCoordinator_GameEvent;
class UClass;

USTRUCT(BlueprintType)
struct CSINPUT_API FCsSettings_Coordinator_GameEvent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Coordinators|Game Event")
	TSoftClassPtr<UCsCoordinator_GameEvent> Class;

	FCsSettings_Coordinator_GameEvent();

	static const FCsSettings_Coordinator_GameEvent& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Coordinator_GameEvent