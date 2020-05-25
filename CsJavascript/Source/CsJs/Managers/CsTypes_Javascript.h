// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Javascript.generated.h"
#pragma once

// FCsJavascriptFileObjects
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSJS_API FCsJavascriptFileObjects
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(Transient)
	UObject* Isolate;

	UPROPERTY(Transient)
	UObject* Context;

	FCsJavascriptFileObjects() :
		Isolate(nullptr),
		Context(nullptr)
	{
	}
};

#pragma endregion FCsJavascriptFileObjects