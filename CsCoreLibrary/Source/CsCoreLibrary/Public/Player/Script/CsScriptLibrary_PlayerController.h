// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_PlayerController.generated.h"

class APlayerController;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_PlayerController : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the First Local Player Controller
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* return					Player Controller
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Player|Controller", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static APlayerController* GetFirstLocal(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the First Local Player Controller
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* @param OutSuccess			(out)
	* return					Player Controller
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Player|Controller", meta = (DisplayName = "Get First Local (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static APlayerController* GetFirstLocalChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get
};