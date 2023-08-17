// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Array.h"

#include "CsSettings_Manager_Javascript.generated.h"

// FCsSettings_Manager_Javascript
#pragma region

USTRUCT(BlueprintType)
struct CSJS_API FCsSettings_Manager_Javascript
{
	GENERATED_USTRUCT_BODY()

public:

	/** Reload a Scripts at Runtime with by the Input associated with Key. 
		Each Script is associated with an Index (the run / execution order). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsJs|Manager|Javascript|Settings")
	TMap<FKey, FCsArray_int32> ReloadScriptsByKeyMap;

	FCsSettings_Manager_Javascript() :
		ReloadScriptsByKeyMap()
	{
	}

	static const FCsSettings_Manager_Javascript& Get();
};

#pragma endregion FCsSettings_Manager_Javascript