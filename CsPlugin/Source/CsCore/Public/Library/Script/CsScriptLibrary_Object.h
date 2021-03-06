// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
};