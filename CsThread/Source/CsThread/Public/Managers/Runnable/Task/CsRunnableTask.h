// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Runnable/CsTypes_Runnable.h"

class UObject;

namespace NCsRunnable
{
	namespace NTask
	{
		DECLARE_DELEGATE(FOnComplete)

		/**
		*/
		struct CSTHREAD_API ITask
		{
		public:

			virtual ~ITask(){}

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
			virtual TArray<FOnComplete>& GetOnComplete_Events() = 0;

			/**
			*/
			virtual TArray<FOnComplete>& GetOnComplete_AsyncEvents() = 0;

			virtual void Reset() = 0;
		};
	}
}