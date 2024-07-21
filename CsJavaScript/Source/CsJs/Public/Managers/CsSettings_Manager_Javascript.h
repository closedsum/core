// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

	/** The number of script objects that can be running at once.
		If this value is changed, the editor needs to restarted. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsJs|Manager|Javascript|Settings", meta = (UIMin = "1", ClampMin = "1"))
	int32 PoolSize;

	/** Path to file to run when a Script is Deactivated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsJs|Manager|Javascript|Settings")
	FString EmptyPath;

	/** Reload a Scripts at Runtime with by the Input associated with Key. 
		Each Script is associated with an Index (the run / execution order). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsJs|Manager|Javascript|Settings")
	TMap<FKey, FCsArray_int32> ReloadScriptsByKeyMap;

	FCsSettings_Manager_Javascript() :
		PoolSize(2),
		EmptyPath(TEXT("Cs/Empty.js")),
		ReloadScriptsByKeyMap()
	{
	}

	static const FCsSettings_Manager_Javascript& Get();

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Javascript