// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsScriptLibrary_Manager_Fade.generated.h"

class UCsManager_Fade;

// NCsFade::NManager::FLibrary
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFade, NManager, FLibrary)

UCLASS()
class CSFADE_API UCsScriptLibrary_Manager_Fade : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	typedef NCsFade::NManager::FLibrary NativeLibrary;

	static void(*LogError)(const FString&);

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
	UFUNCTION(BlueprintPure, Category = "CsFade|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Fade* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the reference to UCsManager_Fade from a WorldContext.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return					UCsManager_Fade.
	*/
	UFUNCTION(BlueprintPure, Category = "CsFade|Library|Manager|Fade", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Fade* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get

public:

	/**
	* 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return					
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool ClearFade(const FString& Context, const UObject* WorldContextObject);

	/**
	* 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return					
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (DisplayName = "Clear Fade (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void ClearFadeChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

	/**
	* Fade the screen from Clear to Black over Time.
	* 
	* @param Context		The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Time"))
	static bool FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time);

	/**
	* Fade the screen from Clear to Black over Time.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (DisplayName = "Fade Clear to Black (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Time"))
	static void FadeClearToBlackChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess);

	/**
	* Fade the screen from Black to Clear over Time.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Time"))
	static bool FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time);

	/**
	* Fade the screen from Black to Clear over Time.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Time
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFade|Library|Manager|Fade", meta = (DisplayName = "Fade Black to Clear (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Time"))
	static void FadeBlackToClearChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess);

	/**
	* Get whether the Fade is Active or not.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsFade|Library|Manager|Fade", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool IsFadeActive(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get whether the Fade is Active or not.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintPure, Category = "CsFade|Library|Manager|Fade", meta = (DisplayName = "Is Fade Active (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool IsFadeActiveChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);
};