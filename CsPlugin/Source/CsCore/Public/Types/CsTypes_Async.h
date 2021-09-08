// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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