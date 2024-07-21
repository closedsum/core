// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Performance.generated.h"

class UCsManager_Performance;

UCLASS()
class CSPERFORMANCE_API UCsScriptLibrary_Manager_Performance : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Performance from a WorldContext.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return					UCsManager_Performance.
	*/
	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Manager|Performance", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Performance* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the reference to UCsManager_Performance from a WorldContext.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return					UCsManager_Performance.
	*/
	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Manager|Performance", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Performance* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get
};