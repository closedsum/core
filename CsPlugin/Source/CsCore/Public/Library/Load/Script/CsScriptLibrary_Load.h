// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Load.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Load : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:
	
	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Load", meta = (AutoCreateRefTerm = "Context,LoadFlags,LoadCodes"))
	static bool LoadObject(const FString& Context, UObject* Object, const int32& LoadFlags, const int32& LoadCodes);

	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Load", meta = (AutoCreateRefTerm = "Context,LoadFlags,LoadCodes"))
	static UObject* LoadSoftClassPtr(const FString& Context, const TSoftClassPtr<UObject>& SoftClass, const int32& LoadFlags, const int32& LoadCodes);
};