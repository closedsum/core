// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

	UPROPERTY(Transient)
	TArray<FString> ExposedObjectNames;

	FCsJavascriptFileObjects() :
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