// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

struct FCsMutex
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