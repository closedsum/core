// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Level/Types/CsTypes_Level_Streaming.h"

#include "CsScriptLibrary_Level_Streaming.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Level_Streaming : public UObject
{
	GENERATED_UCLASS_BODY()

// Load
#pragma region
public:

	/**
	* Load a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return				Whether the load was executing successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static bool Load(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadParams& Params);

	/**
	* Load a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* @param OutSuccess		(out) Whether the load was executing successfully or not.
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (DisplayName = "Load (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static void LoadChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadParams& Params, bool& OutSuccess);

	/**
	* Load a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return				Whether the load was executing successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static bool LoadByPath(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadWithPathParams& Params);

	/**
	* Load a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* @param OutSuccess		(out) Whether the load was executing successfully or not.
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (DisplayName = "Load by Path (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static void LoadByPathChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadWithPathParams& Params, bool& OutSuccess);

#pragma endregion Load

// Unload
#pragma region
public:

	/**
	* Unload a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return				Whether the unload was executing successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static bool Unload(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadParams& Params);

	/**
	* Unload a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* @param OutSuccess		(out) Whether the unload was executing successfully or not.
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (DisplayName = "Unload (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static void UnloadChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadParams& Params, bool& OutSuccess);

	/**
	* Unload a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return				Whether the unload was executing successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static bool UnloadByPath(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadWithPathParams& Params);

	/**
	* Unload a sub-level (a Level already listed in a World's list of streaming levels) with the given parameters.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* @param OutSuccess		(out) Whether the unload was executing successfully or not.
	* return				UCsManager_Level.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Level|Streaming", meta = (DisplayName = "Unload by Path (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Params"))
	static void UnloadByPathChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadWithPathParams& Params, bool& OutSuccess);

#pragma endregion Unload
};