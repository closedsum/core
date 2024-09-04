// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Level/CsTypes_Manager_Level.h"

#include "CsScriptLibrary_Manager_Level.generated.h"

class UCsManager_Level;

// NCsLevel::NManager::FLibrary
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsLevel, NManager, FLibrary)

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Level : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	typedef NCsLevel::NManager::FLibrary NativeLibrary;

	static void(*LogError)(const FString&);

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

// Change Map
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Level", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool HasChangeMapCompleted(const FString& Context, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Level", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static bool ChangeMap(const FString& Context, const UObject* WorldContextObject, const FCsManagerLevel_ChangeMapParams& Params);

#pragma endregion Change Map
};