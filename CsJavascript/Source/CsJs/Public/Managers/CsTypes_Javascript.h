// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsTypes_Javascript.generated.h"

// FCsJavascriptFileObjects
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSJS_API FCsJavascriptFileObjects
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(Transient)
	FGuid Id;

	UPROPERTY(Transient)
	UObject* Isolate;

	UPROPERTY(Transient)
	UObject* Context;

	UPROPERTY(Transient)
	TArray<FString> ExposedObjectNames;

	FCsJavascriptFileObjects() :
		Id(),
		Isolate(nullptr),
		Context(nullptr),
		ExposedObjectNames()
	{
	}

	FORCEINLINE bool IsValidChecked(const FString& Ctxt) const
	{
		checkf(Isolate, TEXT("%s: Isloate is NULL."), *Ctxt);

		checkf(Context, TEXT("%s: Context is NULL."), *Ctxt);
		return true;
	}

	void Shutdown();
};

#pragma endregion FCsJavascriptFileObjects