// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/StreamableManager.h"

// FCsStreamableHandle
#pragma region

struct CSTYPES_API FCsStreamableHandle
{
public:

	//static const FCsStreamableHandle Invalid;

public:

	FGuid Id;

	TSharedPtr<FStreamableHandle> Handle;

	FCsStreamableHandle();

	FORCEINLINE bool operator==(const FCsStreamableHandle& B) const
	{
		return Id == B.Id;
	}

	FORCEINLINE bool operator!=(const FCsStreamableHandle& B) const
	{
		return !(*this == B);
	}

	friend uint32 GetTypeHash(const FCsStreamableHandle& InHandle)
	{
		return GetTypeHash(InHandle.Id);
	}

	FORCEINLINE void Init(const TSharedPtr<FStreamableHandle>& InHandle)
	{
		Handle = InHandle;
		New();
	}

	FORCEINLINE bool IsValid() const
	{
		return Id.IsValid() && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Id = FGuid::NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Id.Invalidate();

		Handle = nullptr;
	}
};

#pragma endregion FCsStreamableHandle