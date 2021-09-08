// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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