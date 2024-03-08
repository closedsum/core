// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_World.generated.h"

class AActor;

UCLASS()
class CSCORE_API UCsScriptLibrary_World : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Get whether the current World is of type: Editor Preview (EWorldType::EditorPreview) or not.
	* 
	* @param WorldContextObject
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|World", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsPlayInEditorPreview(const UObject* WorldContextObject);

	/**
	* Removes the passed in actor to from special network actor list
	*
	* @param Actor	Actor to remove
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|World", meta = (AutoCreateRefTerm = "Context"))
	static void RemoveNetworkActor(const FString& Context, AActor* Actor);
};