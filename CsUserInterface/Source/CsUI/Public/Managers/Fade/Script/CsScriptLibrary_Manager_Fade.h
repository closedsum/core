// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Fade.generated.h"

class UCsManager_Fade;

UCLASS()
class CSUI_API UCsScriptLibrary_Manager_Fade : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Fade from a WorldContext.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return					UCsManager_Fade.
	*/
	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Fade* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the reference to UCsManager_Fade from a WorldContext.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return					UCsManager_Fade.
	*/
	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Manager|Fade", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Fade* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get

public:

	/**
	* fade the screen from Clear to Black over Time.
	* 
	* @param Context		The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsUI|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Time"))
	static bool FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time);

	/**
	* fade the screen from Black to Clear over Time.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsUI|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Time"))
	static bool FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time);
};