// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Time/CsTypes_Update.h"

#include "CsSettings_Manager_Time.generated.h"

// FCsSettings_Manager_Time
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Time
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUpdateGroup, FKey> TogglePauseGroupByKeyMap;
	
	FCsSettings_Manager_Time() :
		TogglePauseGroupByKeyMap()
	{
	}
};

#pragma endregion FCsSettings_Manager_Time