// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_GameStateImpl.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_GameStateImpl : public UObject
{
	GENERATED_UCLASS_BODY()

// ICsGameState_Startup
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Game State", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsStartupComplete(const FString& Context, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Game State", meta = (DisplayName = "Is Startup Complete (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsStartupCompleteChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion ICsGameState_Startup
};