// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsRoutineHandle.generated.h"

USTRUCT(BlueprintType)
struct CSCOROUTINE_API FCsRoutineHandle
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsRoutineHandle Invalid;

public:

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Coroutine")
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Coroutine")
	FGuid Handle;

	FCsRoutineHandle() :
		Index(INDEX_NONE),
		Handle()
	{
	}

	FORCEINLINE bool operator==(const FCsRoutineHandle& B) const
	{
		return Index == B.Index && Handle == B.Handle;
	}

	FORCEINLINE bool operator!=(const FCsRoutineHandle& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE const int32& GetIndex() const { return Index; }

	friend uint32 GetTypeHash(const FCsRoutineHandle& InHandle)
	{
		return GetTypeHash(InHandle.Handle);
	}

	FORCEINLINE bool IsValid() const
	{
		return Index > INDEX_NONE && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Handle = FGuid::NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Handle.Invalidate();
	}

	FORCEINLINE void Invalidate()
	{
		Index = INDEX_NONE;
		Handle.Invalidate();
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("Index: %d Handle: %s"), Index, *(Handle.ToString()));
	}
};