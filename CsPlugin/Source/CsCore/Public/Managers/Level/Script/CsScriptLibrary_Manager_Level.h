// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Level.generated.h"

class UCsManager_Level;

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Level : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Level from a WorldContext.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Level", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Level* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the reference to UCsManager_Level from a WorldContext.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess		(out)
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Level", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Level* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get
};