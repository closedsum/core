// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

DECLARE_DELEGATE(FCsOnRunnableTaskComplete)

class UObject;

/**
*/
struct CSCORE_API ICsRunnableTask
{
public:

	virtual ~ICsRunnableTask(){}

public:

	/**
	*/
	virtual void Execute() = 0;

	/**
	*/
	virtual bool IsRunning() const = 0;

	/**
	*/
	virtual bool IsComplete() const = 0;

	/**
	*/
	virtual TArray<FCsOnRunnableTaskComplete>& GetOnComplete_Events() = 0;

	/**
	*/
	virtual TArray< FCsOnRunnableTaskComplete>& GetOnComplete_AsyncEvents() = 0;

	virtual void Reset() = 0;
};