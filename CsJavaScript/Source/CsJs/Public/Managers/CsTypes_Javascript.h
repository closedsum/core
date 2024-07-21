// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
	int32 Index;

	UPROPERTY(Transient)
	FGuid Id;

	UPROPERTY(Transient)
	UObject* Isolate;

	UPROPERTY(Transient)
	UObject* Context;

	UPROPERTY(Transient)
	TArray<FString> ExposedObjectNames;

	UPROPERTY(Transient)
	FString Path;

	FCsJavascriptFileObjects() :
		Index(INDEX_NONE),
		Id(),
		Isolate(nullptr),
		Context(nullptr),
		ExposedObjectNames(),
		Path()
	{
	}

	FORCEINLINE bool HasValidObjects() const { return IsValid(Isolate) && IsValid(Context); }

	FORCEINLINE bool IsValidChecked(const FString& Ctxt) const
	{
		checkf(IsValid(Isolate), TEXT("%s: Isloate is NULL."), *Ctxt);
		checkf(IsValid(Context), TEXT("%s: Context is NULL."), *Ctxt);
		return true;
	}

	void Init(UObject* Owner);
	void Deactivate(UObject* Owner);
	void Shutdown();
};

#pragma endregion FCsJavascriptFileObjects