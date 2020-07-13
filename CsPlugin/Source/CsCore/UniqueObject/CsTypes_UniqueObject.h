// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Misc/Guid.h"
#pragma once

/**
*/
struct CSCORE_API FCsUniqueObjectId
{
public:

	FGuid Id;

	FCsUniqueObjectId() :
		Id()
	{
	}

	FORCEINLINE friend bool operator==(const FCsUniqueObjectId& Lhs, const FCsUniqueObjectId& Rhs)
	{
		return Lhs.Id == Rhs.Id;
	}

	FORCEINLINE friend bool operator!=(const FCsUniqueObjectId& Lhs, const FCsUniqueObjectId& Rhs)
	{
		return !(Lhs.Id == Rhs.Id);
	}

	void NewId()
	{
		Id = FGuid::NewGuid();
	}
};

FORCEINLINE uint32 GetTypeHash(const FCsUniqueObjectId& b)
{
	return GetTypeHash(b.Id);
}