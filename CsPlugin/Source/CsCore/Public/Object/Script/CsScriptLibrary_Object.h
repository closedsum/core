// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Object.generated.h"


UCLASS()
class CSCORE_API UCsScriptLibrary_Object : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static UObject* ConstructObject(const FString& Context, UObject* Outer, UClass* Class);

	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static bool Object_MarkPendingKill(const FString& Context, UObject* Object);
};