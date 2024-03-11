// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Common.generated.h"

class UGameInstance;

UCLASS()
class CSCORE_API UCsScriptLibrary_Common : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	static UGameInstance* GetGameInstanceFromContext(const FString& Context, const UObject* WorldContextObject);
};