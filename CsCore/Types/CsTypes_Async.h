// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

struct FCsMutex
{
private:
	bool lock;

public:

	FCsMutex()
	{
		Reset();
	}
	~FCsMutex(){}

	void Lock() { lock = true; }
	bool IsLocked() { return lock; }
	void Unlock() { lock = false; }

	void Reset()
	{
		lock = false;
	}
};