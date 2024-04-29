// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_StringTable.generated.h"

class UStringTable;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_StringTable : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|String|Table", meta = (AutoCreateRefTerm = "Context,Key,SourceString"))
	static bool SetSourceString(const FString& Context, UStringTable* StringTable, const FString& Key, const FString& SourceString);
};