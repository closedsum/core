// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsRoutineHandle.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FCsRoutineHandle
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsRoutineHandle Invalid;

public:

	UPROPERTY(BlueprintReadWrite)
	int32 Index;

	UPROPERTY(BlueprintReadOnly)
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
};