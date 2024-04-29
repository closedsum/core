// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

struct CSTYPES_API FCsMutex
{
private:
	bool bLock;

public:

	FCsMutex()
	{
		Reset();
	}
	~FCsMutex(){}

	void Lock() { bLock = true; }
	bool IsLocked() { return bLock; }
	void Unlock() { bLock = false; }

	void Reset()
	{
		bLock = false;
	}
};