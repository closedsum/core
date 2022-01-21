// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_EdEngine.generated.h"

UCLASS()
class CSEDITOR_API UCsScriptLibrary_EdEngine : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|EdEngine", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void AddCreatedObject(const FString& Context, UObject* Object, UObject* Owner);
};