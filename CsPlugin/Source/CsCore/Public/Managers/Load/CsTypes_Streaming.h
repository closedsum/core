// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StreamableManager.h"

// FCsStreamableHandle
#pragma region

struct CSCORE_API FCsStreamableHandle
{
public:

	//static const FCsStreamableHandle Invalid;

public:

	FGuid Id;

	TSharedPtr<FStreamableHandle> Handle;

	FCsStreamableHandle() :
		Id(),
		Handle(nullptr)
	{
	}

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

	FORCEINLINE bool IsValid() const
	{
		return Id.IsValid() && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Id.NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Id.Invalidate();

		Handle = nullptr;
	}
};

#pragma endregion FCsStreamableHandle