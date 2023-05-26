// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_GameInstance.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_GameInstance : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Check if the instance currently running is a Mobile Preview with Editor (WITH_EDITOR == 1).
	* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				Whether the instance running is a Mobile Preview with Editor .
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsMobilePreviewEditor(const FString& Context, const UObject* WorldContextObject);
};