// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsLoadHandle.generated.h"

// FCsLoadHandle
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsLoadHandle
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsLoadHandle Invalid;

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	FGuid Handle;

	FCsLoadHandle() :
		Index(INDEX_NONE),
		Handle()
	{
	}

	FORCEINLINE bool operator==(const FCsLoadHandle& B) const
	{
		return Index == B.Index && Handle == B.Handle;
	}

	FORCEINLINE bool operator!=(const FCsLoadHandle& B) const
	{
		return !(*this == B);
	}

	friend uint32 GetTypeHash(const FCsLoadHandle& InHandle)
	{
		return static_cast<uint32>(InHandle.Index) ^ GetTypeHash(InHandle.Handle);
	}

	FORCEINLINE bool IsValid() const
	{
		return Index > INDEX_NONE && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Handle = Handle.NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Handle.Invalidate();
	}
};

#pragma endregion FCsLoadHandle